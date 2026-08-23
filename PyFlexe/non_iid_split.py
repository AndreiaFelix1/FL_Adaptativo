import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import random
import pickle
import os
from core.dataset.dataset_utils_tf import ManageDatasets

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
SEED = 42
NCLIENTS = [50, 100, 200] #Total Number of Vehicles
TELEPORT_FACTOR = 0.1 #Percent of Teleport Vehicles

#DATASET = "Fashion-MNIST"
#DATASET = "MNIST"
DATASET = "SIGN"
#DATASET = "CIFAR10"
#DATASET = "UCI-HAR"
#DATASET = "Motion-Sense"
#DATASET = "Argoverse2"
#DATASET = "CORL2017"

batch_size = 32
train_size = 0.75 # merge original training set and test set, then split it manually. 
least_samples = batch_size / (1-train_size) # least samples for each client
alpha = 0.1 # for Dirichlet distribution (0.1, 0.5 e 5)

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
    

def split_dirichlet_dataset(x_train, y_train, x_test, y_test, NUM_CLASSES, NCLIENTS, TELEPORT_FACTOR, DATASET, partition="homogeneous"):
    np.random.seed(SEED)
    random.seed(SEED)
    
    dataset_content, dataset_label = x_train, y_train
    dataset_content_test, dataset_label_test = x_test, y_test
    n_train = dataset_content.shape[0]
    n_test = dataset_content_test.shape[0]
    
    if partition == "homogeneous":
        print("partition: ", partition)
        for nclients in NCLIENTS:
            NCLIENTS_RANGE = int((nclients*TELEPORT_FACTOR)+nclients) 
            
            idxs = np.random.permutation(n_train)
            batch_idxs = np.array_split(idxs, NCLIENTS_RANGE)
            net_dataidx_map = {i: batch_idxs[i] for i in range(NCLIENTS_RANGE)}
            
            idxs_test = np.random.permutation(n_test)
            batch_idxs_test = np.array_split(idxs_test, NCLIENTS_RANGE)
            net_dataidx_map_test = {i: batch_idxs_test[i] for i in range(NCLIENTS_RANGE)}
            
            for client in net_dataidx_map.keys():
                idxs = net_dataidx_map[client]
                filename_train = f"./data/{DATASET}/{nclients}/idx_train_{client}.pickle"
                os.makedirs(os.path.dirname(filename_train), exist_ok=True)
                with open(filename_train, 'wb') as handle:
                    pickle.dump(idxs, handle, protocol=pickle.HIGHEST_PROTOCOL)

            for client in net_dataidx_map_test.keys():
                idxs_test = net_dataidx_map_test[client]
                filename_test  = f"./data/{DATASET}/{nclients}/idx_test_{client}.pickle"
                with open(filename_test, 'wb') as handle:
                    pickle.dump(idxs_test, handle, protocol=pickle.HIGHEST_PROTOCOL)
    
    elif partition == "iid-diff-quantity":
        print("partition: ", partition)
        for nclients in NCLIENTS:
            NCLIENTS_RANGE = int((nclients*TELEPORT_FACTOR)+nclients)
            idxs = np.random.permutation(n_train)
            idxs_test = np.random.permutation(n_test)
            
            min_size = 0
            min_require_size = 10
            while min_size < min_require_size:
                proportions = np.random.dirichlet(np.repeat(alpha, NCLIENTS_RANGE))
                proportions = proportions/proportions.sum()
                min_size = np.min(proportions*len(idxs))
                
            proportions = (np.cumsum(proportions)*len(idxs)).astype(int)[:-1]
            batch_idxs = np.split(idxs, proportions)
            net_dataidx_map = {i: batch_idxs[i] for i in range(NCLIENTS_RANGE)}
            
            for i in range(NCLIENTS_RANGE):
                net_dataidx_map[i] = net_dataidx_map[i].tolist()
            
            min_size = 0
            min_require_size = 10
            while min_size < min_require_size:
                proportions = np.random.dirichlet(np.repeat(alpha, NCLIENTS_RANGE))
                proportions = proportions/proportions.sum()
                print("(Test) proportions: ", proportions)
                min_size = np.min(proportions*len(idxs_test))
                print("(Test) min_size: ", min_size, " | min_require_size: ", min_require_size)
                
            proportions = (np.cumsum(proportions)*len(idxs_test)).astype(int)[:-1]
            batch_idxs_test = np.split(idxs_test, proportions)
            net_dataidx_map_test = {i: batch_idxs_test[i] for i in range(NCLIENTS_RANGE)}
            
            for i in range(NCLIENTS_RANGE):
                net_dataidx_map_test[i] = net_dataidx_map_test[i].tolist()
                
            for client in net_dataidx_map.keys():
                idxs = net_dataidx_map[client]
                filename_train = f"./data/{DATASET}/{nclients}/idx_train_{client}.pickle"
                os.makedirs(os.path.dirname(filename_train), exist_ok=True)
                with open(filename_train, 'wb') as handle:
                    pickle.dump(idxs, handle, protocol=pickle.HIGHEST_PROTOCOL)

            for client in net_dataidx_map_test.keys():
                idxs_test = net_dataidx_map_test[client]
                filename_test  = f"./data/{DATASET}/{nclients}/idx_test_{client}.pickle"
                with open(filename_test, 'wb') as handle:
                    pickle.dump(idxs_test, handle, protocol=pickle.HIGHEST_PROTOCOL)

    elif partition == "noniid-labeldir":
        print("partition: ", partition)
        for nclients in NCLIENTS:
            dataidx_map = {}
            dataidx_map_test = {}
            
            idxs = np.array(range(len(dataset_label)))
            idxs_test = np.array(range(len(dataset_label_test)))
            NCLIENTS_RANGE = int((nclients*TELEPORT_FACTOR)+nclients)
            
            X_train = dict(enumerate([[] for _ in range(NCLIENTS_RANGE)]))
            X_test = dict(enumerate([[] for _ in range(NCLIENTS_RANGE)]))
                        
            min_size = 0
            min_size_test = 0
            K = NUM_CLASSES
            N = len(dataset_label)
            NN = len(dataset_label_test)
            
            while min_size < least_samples and min_size_test < least_samples:
            
                idx_batch = [[] for _ in range(NCLIENTS_RANGE)]
                idx_batch_test = [[] for _ in range(NCLIENTS_RANGE)]
                
                for k in range(K):
                
                    idx_k = np.where(dataset_label == k)[0]
                    idx_k_test = np.where(dataset_label_test == k)[0]
                    
                    np.random.shuffle(idx_k)
                    np.random.shuffle(idx_k_test)
                    
                    original_proportions = np.random.dirichlet(np.repeat(alpha, NCLIENTS_RANGE))
                    proportions = original_proportions
                    proportions = np.array([p * (len(idx_j) < N/NCLIENTS_RANGE) for p, idx_j in zip(proportions, idx_batch)])               
                    proportions = proportions/proportions.sum()
                    proportions = (np.cumsum(proportions)*len(idx_k)).astype(int)[:-1]
                    idx_batch = [idx_j + idx.tolist() for idx_j,idx in zip(idx_batch, np.split(idx_k, proportions))]
                    for idx_list, chave in zip(idx_batch, X_train.keys()):
                        if len(idx_list) == 0:
                            continue
                        for idx in idx_list:
                            if idx not in X_train[chave]:
                                X_train[chave].append(idx)
                    
                    proportions = original_proportions
                    proportions = np.array([p*(len(idx_j) < NN/NCLIENTS_RANGE) for p,idx_j in zip(proportions, idx_batch_test)])
                    proportions = proportions/proportions.sum()
                    proportions = (np.cumsum(proportions)*len(idx_k_test)).astype(int)[:-1]                
                    idx_batch_test = [idx_j + idx.tolist() for idx_j,idx in zip(idx_batch_test,np.split(idx_k_test, proportions))]
                    for idx_list, chave in zip(idx_batch_test, X_test.keys()):
                        if len(idx_list) == 0:
                            continue
                        for idx in idx_list:
                            if idx not in X_test[chave]:
                                X_test[chave].append(idx)
                                
                    idx_batch = list(X_train.values())
                    idx_batch_test = list(X_test.values())
                    
                    min_size = min([len(idx_j) for idx_j in idx_batch])
                    min_size_test = min([len(idx_j) for idx_j in idx_batch_test])
                    print("(Train) min_size: ", min_size, " | least_samples: ", least_samples)
                    print("(Test) min_size_test: ", min_size_test, " | least_samples: ", least_samples)
            
                    
            for j in range(NCLIENTS_RANGE):
                dataidx_map[j] = idx_batch[j]
                dataidx_map_test[j] = idx_batch_test[j]

            for client in range(NCLIENTS_RANGE):
                idxs = dataidx_map[client]
                idxs_test = dataidx_map_test[client]
                filename_train = f"./data/{DATASET}/{nclients}/idx_train_{client}.pickle"
                filename_test  = f"./data/{DATASET}/{nclients}/idx_test_{client}.pickle"
                os.makedirs(os.path.dirname(filename_train), exist_ok=True)
                with open(filename_train, 'wb') as handle:
                    pickle.dump(idxs, handle, protocol=pickle.HIGHEST_PROTOCOL)
                with open(filename_test, 'wb') as handle:
                    pickle.dump(idxs_test, handle, protocol=pickle.HIGHEST_PROTOCOL)


def split_dataset(x_train, y_train, x_test, y_test, NUM_CLASSES, NCLIENTS, TELEPORT_FACTOR, DATASET):
    for nclients in NCLIENTS:
        nclients_range = int((nclients*TELEPORT_FACTOR)+nclients)
        for _ in range(nclients_range):
            if DATASET == "CORL2017":
                random.shuffle(dataset_train)
                random.shuffle(dataset_test)
                num_files_train = random.randint(2, len(dataset_train)/2.0)
                num_files_test = random.randint(2, len(dataset_test)/2.0)
                files_train = random.sample(dataset_train, num_files_train)
                files_test = random.sample(dataset_test, num_files_test)
                
                filename_train = f"./data/{DATASET}/{nclients}/idx_train_{_}.pickle"
                filename_test  = f"./data/{DATASET}/{nclients}/idx_test_{_}.pickle"
                os.makedirs(os.path.dirname(filename_train), exist_ok=True)
                os.makedirs(os.path.dirname(filename_test), exist_ok=True)
                		
                with open(filename_train, 'wb') as handle:
                    pickle.dump(files_train, handle, protocol=pickle.HIGHEST_PROTOCOL)
                with open(filename_test, 'wb') as handle:
                    pickle.dump(files_test, handle, protocol=pickle.HIGHEST_PROTOCOL)
                    
            else:
                index_train   = []
                index_test    = []
                classes_2b_selected = random.randint(2, 6)
                for selected_class in range(classes_2b_selected):
                    label = random.randint(0, NUM_CLASSES-1)
                    index_labels_train = np.where(y_train == label)
                    index_labels_test = np.where(y_test == label)
                    sample_size_train = random.randint(1, 40) / 100.0
                    sample_size_test = random.randint(1, 30) / 100.0
                    
                    index_sampled_train = random.choices(index_labels_train[0], k=int(sample_size_train * len(index_labels_train[0])))
                    index_sampled_test = random.choices(index_labels_test[0], k=int(sample_size_test * len(index_labels_test[0])))
                    
                    index_train += [item for item in index_sampled_train]
                    index_test += [item for item in index_sampled_test]

                    filename_train = f"./data/{DATASET}/{nclients}/idx_train_{_}.pickle"
                    filename_test  = f"./data/{DATASET}/{nclients}/idx_test_{_}.pickle"
                    
                    os.makedirs(os.path.dirname(filename_train), exist_ok=True)
                    os.makedirs(os.path.dirname(filename_test), exist_ok=True)
                    
                    with open(filename_train, 'wb') as handle:
                        pickle.dump(index_train, handle, protocol=pickle.HIGHEST_PROTOCOL)
                    
                    with open(filename_test, 'wb') as handle:
                        pickle.dump(index_test, handle, protocol=pickle.HIGHEST_PROTOCOL)


def split_validation(x_train, y_train, NUM_CLASSES, DATASET):
    dict_dataset = {}
    counter = 0
    for x, y in zip(x_train, y_train):
        if y not in dict_dataset.keys():
            dict_dataset[y] = []
        dict_dataset[y].append(counter)
        counter = counter + 1
        
    for percent in range(1, 10, 1):
        for chave in dict_dataset.keys():
            len_class = len(dict_dataset[chave])
            num_data = int(len_class*(percent/100.0))
            print(chave, " - ", len_class, " ", percent,"% -> ", num_data)
            index_dataset = dict_dataset[chave][0:num_data]
            filename_train = f"./data/{DATASET}/%{percent}%/idx_train_{chave}.pickle"
            os.makedirs(os.path.dirname(filename_train), exist_ok=True)
            with open(filename_train, 'wb') as handle:
                pickle.dump(index_dataset, handle, protocol=pickle.HIGHEST_PROTOCOL)


def plot_data_distribution(y_train, y_test, NUM_CLASSES, NCLIENTS, TELEPORT_FACTOR, DATASET):
    for nclients in NCLIENTS:
        nclients_range = int((nclients*TELEPORT_FACTOR)+nclients)
        dict_train_client = {}
        dict_test_client = {}
        for _ in range(nclients_range):
            filename_train = f"./data/{DATASET}/{nclients}/idx_train_{_}.pickle"
            filename_test  = f"./data/{DATASET}/{nclients}/idx_test_{_}.pickle"
        
            with open(filename_train, 'rb') as handle:
                idx_train = pickle.load(handle)
            unique, counts = np.unique(y_train[idx_train], return_counts=True)
            dict_train_client[_] = dict(zip(unique, counts))          
            
            with open(filename_test, 'rb') as handle:
                idx_test = pickle.load(handle)
            unique, counts = np.unique(y_test[idx_test], return_counts=True)
            dict_test_client[_] = dict(zip(unique, counts))
        
        for chave in dict_train_client.keys():
            plt.clf()
            plt.cla()
            plt.close()
            
            names = list(dict_train_client[chave].keys())
            values = list(dict_train_client[chave].values())
            
            colors = []
            for name in names:
                colors.append(dict_colors[str(name)])
            
            plt.bar(range(len(dict_train_client[chave])), values, tick_label=names, edgecolor="black", color=colors)
            title = "(Train) Client " + str(chave)
            plt.title(title, fontsize=18)
            plt.xticks(fontsize=6)
            plt.yticks(fontsize=18)
            filename_train = f"./{DATASET}_{nclients}_{chave}_train.png"
            plt.savefig(filename_train, format="png")

        for chave in dict_test_client.keys():
            plt.clf()
            plt.cla()
            plt.close()
            
            names = list(dict_test_client[chave].keys())
            values = list(dict_test_client[chave].values())
            
            colors = []
            for name in names:
                colors.append(dict_colors[str(name)])
            
            plt.bar(range(len(dict_test_client[chave])), values, tick_label=names, edgecolor="black", color=colors)
            title = "(Test) Client " + str(chave)
            plt.title(title, fontsize=18)
            plt.xticks(fontsize=6)
            plt.yticks(fontsize=18)
            filename_test = f"./{DATASET}_{nclients}_{chave}_test.png"
            plt.savefig(filename_test, format="png")
            
            
#split_validation(x_train, y_train, NUM_CLASSES, DATASET)
#split_dataset(x_train, y_train, x_test, y_test, NUM_CLASSES, NCLIENTS, TELEPORT_FACTOR, DATASET)
#split_dirichlet_dataset(x_train, y_train, x_test, y_test, NUM_CLASSES, NCLIENTS, TELEPORT_FACTOR, DATASET, "homogeneous")
#split_dirichlet_dataset(x_train, y_train, x_test, y_test, NUM_CLASSES, NCLIENTS, TELEPORT_FACTOR, DATASET, "iid-diff-quantity") #TODO
split_dirichlet_dataset(x_train, y_train, x_test, y_test, NUM_CLASSES, NCLIENTS, TELEPORT_FACTOR, DATASET, "noniid-labeldir")
plot_data_distribution(y_train, y_test, NUM_CLASSES, NCLIENTS, TELEPORT_FACTOR, DATASET)