import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import random
import pickle5  as pickle
import os
from glob import glob
from scipy.stats import entropy
from core.dataset.dataset_utils_tf import ManageDatasets

def entropy_bits(labels, base=None):
    value,counts = np.unique(labels, return_counts=True)
    return entropy(counts, base=base)

dict_colors = {
    "0": "#DCDCDC", 
    "1": "#6A5ACD", 
    "2": "#6495ED", 
    "3": "#00CED1",
    "4": "#7FFFD4",
    "5": "#98FB98",
    "6": "#7FFF00",
    "7": "#F5DEB3",
    "8": "#FA8072",
    "9": "#DDA0DD",
    "10": "#DCDCDC", 
    "11": "#6A5ACD", 
    "12": "#6495ED", 
    "13": "#00CED1",
    "14": "#7FFFD4",
    "15": "#98FB98",
    "16": "#7FFF00",
    "17": "#F5DEB3",
    "18": "#FA8072",
    "19": "#DDA0DD",
    "20": "#DCDCDC", 
    "21": "#6A5ACD", 
    "22": "#6495ED", 
    "23": "#00CED1",
    "24": "#7FFFD4",
    "25": "#98FB98",
    "26": "#7FFF00",
    "27": "#F5DEB3",
    "28": "#FA8072",
    "29": "#DDA0DD",
    "30": "#DCDCDC", 
    "31": "#6A5ACD", 
    "32": "#6495ED", 
    "33": "#00CED1",
    "34": "#7FFFD4",
    "35": "#98FB98",
    "36": "#7FFF00",
    "37": "#F5DEB3",
    "38": "#FA8072",
    "39": "#DDA0DD",
    "40": "#DCDCDC", 
    "41": "#6A5ACD", 
    "42": "#6495ED",
}

os.environ["TF_CPP_MIN_LOG_LEVEL"] = "3"
NCLIENTS = [50, 100, 200] #Total Number of Vehicles

#DATASET = "Fashion-MNIST"
DATASET = "MNIST"
#DATASET = "SIGN"
#DATASET = "CIFAR10"
#DATASET = "UCI-HAR"
#DATASET = "Motion-Sense"
#DATASET = "Argoverse2"
#DATASET = "CORL2017"

if DATASET == "Fashion-MNIST":
    x_train, y_train, x_test, y_test, NUM_CLASSES = ManageDatasets(0).select_dataset(dataset_name="FMNIST", n_clients=1, non_iid=False) #All Data
    NUM_CLASSES = 10
elif DATASET == "CIFAR10":
    x_train, y_train, x_test, y_test, NUM_CLASSES = ManageDatasets(0).select_dataset(dataset_name="CIFAR10", n_clients=1, non_iid=False) #All Data
    NUM_CLASSES = 10
elif DATASET == "SIGN":
    x_train, y_train, x_test, y_test, NUM_CLASSES = ManageDatasets(0).select_dataset(dataset_name="SIGN", n_clients=1, non_iid=False) #All Data
    y_train = np.where(y_train==1)[1]
    y_test = np.where(y_test==1)[1]
    NUM_CLASSES = 43
elif DATASET == "UCI-HAR":
    x_train, y_train, x_test, y_test, NUM_CLASSES = ManageDatasets(0).select_dataset(dataset_name="UCI-HAR", n_clients=1, non_iid=False) #All Data
    NUM_CLASSES = 6 #[WALKING, WALKING_UPSTAIRS, WALKING_DOWNSTAIRS, SITTING, STANDING, LAYING]
elif DATASET == "Motion-Sense":
    x_train, y_train, x_test, y_test, NUM_CLASSES = ManageDatasets(0).select_dataset(dataset_name="Motion-Sense", n_clients=1, non_iid=False) #All Data
    NUM_CLASSES = 6 #[dws: downstairs, ups: upstairs, sit: sitting, std: standing, wlk: walking, jog: jogging]
elif DATASET == "Argoverse2":
    x_train, x_test, x_test, y_test, NUM_CLASSES = ManageDatasets(0).select_dataset(dataset_name="Motion-Sense", n_clients=1, non_iid=False) #All Data
    NUM_CLASSES = 6 
elif DATASET == "CORL2017":
    dataset_train, dataset_test, NUM_CLASSES = ManageDatasets(0).select_dataset(dataset_name="CORL2017", n_clients=1, non_iid=False) #All Data
else:
    x_train, y_train, x_test, y_test, NUM_CLASSES = ManageDatasets(0).select_dataset(dataset_name="MNIST", n_clients=1, non_iid=False) #All Data
    NUM_CLASSES = 10

for nclients in NCLIENTS:
    print("nclients: ", nclients)
    filesTrain = glob(f"./data/{DATASET}/{nclients}/idx_train_*.pickle")
    filesTest = glob(f"./data/{DATASET}/{nclients}/idx_test_*.pickle")
    dict_train_client = {}
    dict_test_client = {}
    for fileTrain, fileTest in zip(filesTrain, filesTest):
        clientID = int(fileTrain.split("_")[-1].replace(".pickle",""))
        with open(fileTrain, 'rb') as handle:
            idx_train = pickle.load(handle)
        unique, counts = np.unique(y_train[idx_train], return_counts=True)
        dict_train_client[clientID] = dict(zip(unique, counts))
        entropy_train = entropy_bits(y_train[idx_train])
        print(clientID, " - Entropy(Train): ", entropy_train)

        plt.clf()
        plt.cla()
        plt.close()
        
        names = list(dict_train_client[clientID].keys())
        values = list(dict_train_client[clientID].values())
        
        colors = []
        for name in names:
            colors.append(dict_colors[str(name)])
        
        plt.bar(range(len(dict_train_client[clientID])), values, tick_label=names, edgecolor="black", color=colors)
        title = "(Train) Client " + str(clientID)
        plt.title(title, fontsize=18)
        plt.xticks(fontsize=18)
        plt.yticks(fontsize=18)
        filename_train = f"./{DATASET}_{nclients}_{clientID}_{entropy_train}_train.png"
        plt.savefig(filename_train, format="png")