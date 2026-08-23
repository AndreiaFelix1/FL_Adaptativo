import tensorflow as tf
import numpy as np
import random
import pickle as pickle
import pandas as pd
import os
from PIL import Image
from glob import glob
import cv2
import gc
import h5py
from sklearn.model_selection import train_test_split
import csv
from core.dataset.Motion_Sense_Splitter import DataFrameSplitter
#from sklearn.preprocessing import Normalizer

import logging
logging.getLogger("tensorflow").setLevel(logging.ERROR)

#VIVA-BEM
ALL_SUBJECTS = ['8258170', '1360686', '844359', '1449548', '4426783', '8686948', 
             '2638030', '3997827', '8692923', '3509524', '1455390', '7749105', 
             '1066528', '781756', '5498603', '9106476', '5132496', '2598705', 
             '5383425', '46343', '4314139', '9961348', '8530312', '4018081', 
             '8173033', '1818471', '6220552', '9618981', 
             '759667', '8000685', '5797046']

ALL_SUBJECTS_GROUP = {'8258170':0, '1360686':1, '844359':2, '1449548':3, '4426783':4, '8686948':5, 
             '2638030':6, '3997827':7, '8692923':8, '3509524':9, '1455390':10, '7749105':11, 
             '1066528':12, '781756':13, '5498603':14, '9106476':15, '5132496':16, '2598705':17, 
             '5383425':18, '46343':19, '4314139':20, '9961348':21, '8530312':22, '4018081':23, 
             '8173033':24, '1818471':25, '6220552':26, '9618981':27, 
             '759667':28, '8000685':29, '5797046':30}

NUM_CLASSES = 2
CLASS_WEIGHTS_DICT ={0:12., 1:1.}

def get_dictionaries(caminhos, SIZE):
    imgs_dict = {}
    labels_dict = {}
    imgs_list = []
    labels_list = []
    groups_list = []

    for caminho in caminhos:
        filenames = sorted(os.listdir(caminho))
        print(f"Total de arquivos em {caminho}: {len(filenames)}")
        
        id_name_atual = None

        for img_name in filenames:
            if ".png" not in img_name:
                continue
            pos_id = img_name.find("_")
            id_name = img_name[:pos_id]
            img_path = os.path.join(caminho, img_name)
            img = Image.open(img_path).resize((SIZE, SIZE), Image.BILINEAR).convert('RGB')
            r, g, b = img.split()
            img_bgr = Image.merge("RGB", (b, g, r))
            img_np = np.array(img_bgr)
            if id_name_atual != id_name:
                if id_name_atual is not None:
                    imgs_dict[id_name_atual] = imgs
                    labels_dict[id_name_atual] = np.asarray(labels)
                    print(f"{id_name_atual}: {len(imgs)} imagens")
                
                id_name_atual = id_name
                imgs = []
                labels = []
            imgs.append(img_np)
            labels.append(int(img_name[-5]))
            imgs_list.append(img_np)
            labels_list.append(int(img_name[-5]))
            groups_list.append(ALL_SUBJECTS_GROUP.get(id_name_atual, None))
        imgs_dict[id_name_atual] = imgs
        labels_dict[id_name_atual] = np.asarray(labels)
        print(f"{id_name_atual}: {len(imgs)} imagens")
    
    print(f"GROUP: {len(groups_list)}, imgs: {len(imgs_list)}, labels: {len(labels_list)}")
    return labels_dict, imgs_dict, np.array(imgs_list), np.array(labels_list), np.array(groups_list)

class DataSplit(object):
    def __init__(self, training_set, testing_set):
        self.training_set = training_set
        self.testing_set = testing_set
    
    def get_trainSet(self):
        return self.training_set

    def set_trainSet(self, train_set):
        self.training_set = train_set

    def get_testSet(self):
        return self.testing_set

    def set_testSet(self, testing_set):
        self.testing_set = testing_set

def get_splits_kfold():
    ALL_SUBJECTS = ['8258170', '1360686', '844359', '1449548', '4426783', '8686948', 
             '2638030', '3997827', '8692923', '3509524', '1455390', '7749105', 
             '1066528', '781756', '5498603', '9106476', '5132496', '2598705', 
             '5383425', '46343', '4314139', '9961348', '8530312', '4018081', 
             '8173033', '1818471', '6220552', '9618981', 
             '759667', '8000685', '5797046']

    fold1_teste = ['4426783', '8686948', '8692923', '7749105', '5498603', '4018081', '9618981']
    fold2_teste = ['844359', '781756', '2598705', '8173033', '759667', '8000685']
    fold3_teste = ['1360686', '2638030', '3997827', '1066528', '5132496', '5383425']
    fold4_teste = ['8258170', '1449548', '3509524', '1455390', '8530312', '1818471']
    fold5_teste = ['9106476', '46343', '4314139', '9961348', '6220552', '5797046']
    testes = [fold1_teste, fold2_teste, fold3_teste , fold4_teste, fold5_teste]
    fold1_train = []
    fold2_train = []
    fold3_train = []
    fold4_train = []
    fold5_train = []

    for subject in ALL_SUBJECTS:
        if subject not in fold1_teste:
            fold1_train.append(subject)
        if subject not in fold2_teste:
            fold2_train.append(subject)
        if subject not in fold3_teste:
            fold3_train.append(subject)
        if subject not in fold4_teste:
            fold4_train.append(subject)
        if subject not in fold5_teste:
            fold5_train.append(subject)

    split1 = DataSplit(training_set=fold1_train, testing_set=fold1_teste)
    split2 = DataSplit(training_set=fold2_train, testing_set=fold2_teste)
    split3 = DataSplit(training_set=fold3_train, testing_set=fold3_teste)
    split4 = DataSplit(training_set=fold4_train, testing_set=fold4_teste)
    split5 = DataSplit(training_set=fold5_train, testing_set=fold5_teste)
    SPLITS_FOLD = [split1, split2, split3, split4, split5]
    return SPLITS_FOLD

def get_dictionaries_kfold(caminhos, SIZE):
    caminhos = glob(caminhos+"/*")
    labels_dict, imgs_dict, imgs_array, labels_array, groups_array = get_dictionaries(caminhos, SIZE)
    data_splits = get_splits_kfold()
    return labels_dict, imgs_dict, data_splits

def sleep_wake_label(labels, num_classes):
    sleep_wake = []
    if num_classes == 2:            ## sono & vigilia
        for label in labels:
            if label > 0:           ## vigilia
                sleep_wake.append(1)
            else:                   ## sono
                sleep_wake.append(0)
    elif num_classes == 3:
        for label in labels:
            if label == 0:          ## vigilia
                sleep_wake.append(0)
            elif label == 5:        ## rem
                sleep_wake.append(2)
            else:                   ## todos nrem
                sleep_wake.append(1)
    return np.asarray(sleep_wake)

def get_inputs(data_split, dict_features, dict_labels, num_classes):
    subjects_train_keys = list(data_split.training_set)
    subjects_test_keys = list(data_split.testing_set)

    dict_train_features = {chave: valor for chave, valor in dict_features.items() if chave in subjects_train_keys}
    dict_train_labels = {chave: valor for chave, valor in dict_labels.items() if chave in subjects_train_keys}

    dict_test_features = {chave: valor for chave, valor in dict_features.items() if chave in subjects_test_keys}
    dict_test_labels = {chave: valor for chave, valor in dict_labels.items() if chave in subjects_test_keys}

    array_train_features = np.vstack([valor for chave, valor in dict_train_features.items()])
    array_train_labels = np.hstack([valor for chave, valor in dict_train_labels.items()])
    array_train_labels = sleep_wake_label(array_train_labels, num_classes)

    array_test_features = np.vstack([valor for chave, valor in dict_test_features.items()])
    array_test_labels = np.hstack([valor for chave, valor in dict_test_labels.items()])
    array_test_labels = sleep_wake_label(array_test_labels, num_classes)

    list_train_labels = array_train_labels.tolist()

    return array_train_features, array_train_labels, array_test_features, array_test_labels, list_train_labels
#VIVA-BEM

class ManageDatasets():
    def __init__(self, cid):
        self.cid = cid
        
    def load_Argoverse2(self, n_clients, non_iid=False):
        print("Argoverse2!")
        print("ID: ", self.cid, " numClients: ", n_clients, " nonIID:", non_iid)
        if non_iid:
            print("Non-IID n_clients:", n_clients, " cid: ", self.cid)
            with open(f'data/MNIST/{n_clients}/idx_train_{self.cid}.pickle', 'rb') as handle:
                idx_train = pickle.load(handle)

            with open(f'data/MNIST/{n_clients}/idx_test_{self.cid}.pickle', 'rb') as handle:
                idx_test = pickle.load(handle)

            (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
            x_train, x_test = x_train/255.0, x_test/255.0

            x_train = x_train[idx_train]
            x_test  = x_test[idx_test]
            
            y_train = y_train[idx_train]
            y_test  = y_test[idx_test]
        else:
            (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
            x_train, x_test                      = x_train/255.0, x_test/255.0
            #x_train, y_train, x_test, y_test     = self.slipt_dataset(x_train, y_train, x_test, y_test, n_clients)

        return x_train, y_train, x_test, y_test, -1
    
    def batch_generator(self, file_names, batch_size=200, masks=None):
        file_idx = -1
        while True:
            if file_idx > len(file_names):
                file_idx = 0
            file_idx = file_idx + 1
            batch_x = []
            batch_y = []
            batch_s = []
            for i in range(0, batch_size):
                data = h5py.File(file_names[file_idx], 'r')
                for mask in masks:
                    if data['targets'][i][24] == mask:
                        batch_x.append(data['rgb'][i])
                        batch_y.append(data['targets'][i][:3])
                        batch_s.append(data['targets'][i][10])
                    if mask == 1:
                        batch_x.append(data['rgb'][i])
                        batch_s.append(data['targets'][i][10])
                data.close()
                gc.collect()
            if masks[0] == 1:
                yield ([np.array(batch_x)], [np.array(batch_s)])
            else:
                yield ([np.array(batch_x), np.array(batch_s)], [np.array(batch_s) if mask == 1 else np.array(batch_y) for mask in masks])
        
    def load_CORL2017(self, n_clients, non_iid=False):
        print("CORL2017!")
        print("ID: ", self.cid, " numClients: ", n_clients, " nonIID:", non_iid)
        dataset_train = glob("data/CORL2017/SeqTrain/*")
        dataset_test = glob("data/CORL2017/SeqVal/*")
        if non_iid:
            with open(f'data/CORL2017/{n_clients}/idx_train_{self.cid}.pickle', 'rb') as handle:
                dataset_train = pickle.load(handle)

            with open(f'data/CORL2017/{n_clients}/idx_test_{self.cid}.pickle', 'rb') as handle:
                dataset_test = pickle.load(handle)
        
        return dataset_train, dataset_test, -1

    def load_UCIHAR(self, n_clients, non_iid=False):
        print("UCI-HAR!")
        print("ID: ", self.cid, " numClients: ", n_clients, " nonIID:", non_iid)
        x_train = pd.read_csv('data/UCI-HAR/train/X_train.txt', delim_whitespace=True, header=None)
        x_train = x_train.values.tolist()
        x_train = np.array(x_train)
        
        y_train = pd.read_csv('data/UCI-HAR/train/y_train.txt', delim_whitespace=True, header=None)
        y_train = y_train.values.tolist()
        y_train = np.array(y_train)
        
        x_test = pd.read_csv('data/UCI-HAR/test/X_test.txt', delim_whitespace=True, header=None)
        x_test = x_test.values.tolist()
        x_test = np.array(x_test)
        
        y_test = pd.read_csv('data/UCI-HAR/test/y_test.txt', delim_whitespace=True, header=None)
        y_test = y_test.values.tolist()
        y_test = np.array(y_test)
        if non_iid:
            with open(f'data/UCI-HAR/{n_clients}/idx_train_{self.cid}.pickle', 'rb') as handle:
                idx_train = pickle.load(handle)

            with open(f'data/UCI-HAR/{n_clients}/idx_test_{self.cid}.pickle', 'rb') as handle:
                idx_test = pickle.load(handle)
                
            x_train = x_train[idx_train]
            x_test  = x_test[idx_test]

            y_train = y_train[idx_train]
            y_test  = y_test[idx_test]


        return x_train, y_train, x_test, y_test, 6
        
    def create_MotionSenseDataset(self):
        folder_name = "data/Motion-Sense/A_DeviceMotion_data"
        mode="raw" #raw or mag
        labeled=True
        sdt = ["attitude", "gravity", "rotationRate", "userAcceleration"]
        ds_list = pd.read_csv("data/Motion-Sense/data_subjects_info.csv")
        ACT_LABELS = ["dws","ups", "wlk", "jog", "std", "sit"]
        TRIAL_CODES = {
            ACT_LABELS[0]:[1,2,11],
            ACT_LABELS[1]:[3,4,12],
            ACT_LABELS[2]:[7,8,15],
            ACT_LABELS[3]:[9,16],
            ACT_LABELS[4]:[6,14],
            ACT_LABELS[5]:[5,13]
        }
        act_labels = ACT_LABELS [0:6]
        trial_codes = [TRIAL_CODES[act] for act in act_labels]
        
        dt_list = []
        for t in sdt:
            if t != "attitude":
                dt_list.append([t+".x",t+".y",t+".z"])
            else:
                dt_list.append([t+".roll", t+".pitch", t+".yaw"])				
        
        num_data_cols = len(dt_list) if mode == "mag" else len(dt_list*3)
        if labeled:
            dataset = np.zeros((0,num_data_cols+7)) # "7" --> [act, code, weight, height, age, gender, trial]
        else:
            dataset = np.zeros((0,num_data_cols))
        
        for sub_id in ds_list["code"]:
            for act_id, act in enumerate(act_labels):
                for trial in trial_codes[act_id]:
                    fname = folder_name+'/'+act+'_'+str(trial)+'/sub_'+str(int(sub_id))+'.csv'
                    raw_data = pd.read_csv(fname)
                    raw_data = raw_data.drop(['Unnamed: 0'], axis=1)
                    vals = np.zeros((len(raw_data), num_data_cols))
                    for x_id, axes in enumerate(dt_list):
                        if mode == "mag":
                            vals[:,x_id] = (raw_data[axes]**2).sum(axis=1)**0.5
                        else:
                            vals[:,x_id*3:(x_id+1)*3] = raw_data[axes].values
                        vals = vals[:,:num_data_cols]
                    if labeled:
                        lbls = np.array([[act_id,
                                sub_id-1,
                                ds_list["weight"][sub_id-1],
                                ds_list["height"][sub_id-1],
                                ds_list["age"][sub_id-1],
                                ds_list["gender"][sub_id-1],
                                trial
                                ]]*len(raw_data), dtype=int)
                        vals = np.concatenate((vals, lbls), axis=1)
                    dataset = np.append(dataset,vals, axis=0)
        
        cols = []
        for axes in dt_list:
            if mode == "raw":
                cols += axes
            else:
                cols += [str(axes[0][:-2])]
        
        if labeled:
            cols += ["act", "id", "weight", "height", "age", "gender", "trial"]
        dataset = pd.DataFrame(data=dataset, columns=cols)
        dfs = DataFrameSplitter(method="trials")
        train_data, test_data = dfs.train_test_split(dataset=dataset, labels = ("id","trial"), trial_col='trial', train_trials=[1.,2.,3.,4.,5.,6.,7.,8.,9.], verbose=2)
        
        Features = dataset.columns[:-7]
        labels_or_info = dataset.columns[-7:]
        
        x_train = train_data[Features]
        y_train = train_data["act"]

        x_test = test_data[Features]
        y_test = test_data["act"]	
        
        x_train.to_csv("data/Motion-Sense/x_train.csv", index=False)
        x_test.to_csv("data/Motion-Sense/x_test.csv", index=False)
        y_train.to_csv("data/Motion-Sense/y_train.csv", index=False)
        y_test.to_csv("data/Motion-Sense/y_test.csv", index=False)	        


    def load_MotionSense(self, n_clients, non_iid=False):
        print("Motion Sense!")
        print("ID: ", self.cid, " numClients: ", n_clients, " nonIID:", non_iid)		
        x_train = pd.read_csv('data/Motion-Sense/x_train.csv', header=1)
        x_train = x_train.values.tolist()
        x_train = np.array(x_train)
        
        y_train = pd.read_csv('data/Motion-Sense/y_train.csv', header=1)
        y_train = y_train.values.tolist()
        y_train = np.array(y_train)
        
        x_test = pd.read_csv('data/Motion-Sense/x_test.csv', header=1)
        x_test = x_test.values.tolist()
        x_test = np.array(x_test)
        
        y_test = pd.read_csv('data/Motion-Sense/y_test.csv', header=1)
        y_test = y_test.values.tolist()
        y_test = np.array(y_test)
        
        if non_iid:
            print("Non-IID n_clients:", n_clients, " cid: ", self.cid)
            with open(f'data/Motion-Sense/{n_clients}/idx_train_{self.cid}.pickle', 'rb') as handle:
                idx_train = pickle.load(handle)

            with open(f'data/Motion-Sense/{n_clients}/idx_test_{self.cid}.pickle', 'rb') as handle:
                idx_test = pickle.load(handle)
                
            x_train = x_train[idx_train]
            x_test  = x_test[idx_test]

            y_train = y_train[idx_train]
            y_test  = y_test[idx_test]  
        
        return x_train, y_train, x_test, y_test, 24


    def load_MNIST(self, n_clients, non_iid=False):
        print("MNIST!")
        print("ID: ", self.cid, " numClients: ", n_clients, " nonIID:", non_iid)
        if non_iid:
            print("Non-IID n_clients:", n_clients, " cid: ", self.cid)
            with open(f'data/MNIST/{n_clients}/idx_train_{self.cid}.pickle', 'rb') as handle:
                idx_train = pickle.load(handle)

            with open(f'data/MNIST/{n_clients}/idx_test_{self.cid}.pickle', 'rb') as handle:
                idx_test = pickle.load(handle)

            (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
            x_train, x_test = x_train/255.0, x_test/255.0

            x_train = x_train[idx_train]
            x_test  = x_test[idx_test]
            
            y_train = y_train[idx_train]
            y_test  = y_test[idx_test]
        else:
            (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
            x_train, x_test                      = x_train/255.0, x_test/255.0

        return x_train, y_train, x_test, y_test, 10
        
    def load_FMNIST(self, n_clients, non_iid=False):
        print("Fashion-MNIST!")
        if non_iid:
            with open(f'data/Fashion-MNIST/{n_clients}/idx_train_{self.cid}.pickle', 'rb') as handle:
                idx_train = pickle.load(handle)

            with open(f'data/Fashion-MNIST/{n_clients}/idx_test_{self.cid}.pickle', 'rb') as handle:
                idx_test = pickle.load(handle)

            (x_train, y_train), (x_test, y_test) = tf.keras.datasets.fashion_mnist.load_data()
            x_train, x_test = x_train/255.0, x_test/255.0

            x_train = x_train[idx_train]
            x_test  = x_test[idx_test]
            
            y_train = y_train[idx_train]
            y_test  = y_test[idx_test]
        else:
            (x_train, y_train), (x_test, y_test) = tf.keras.datasets.fashion_mnist.load_data()
            x_train, x_test                      = x_train/255.0, x_test/255.0

        return x_train, y_train, x_test, y_test, 10
        

    def load_CIFAR10(self, n_clients, non_iid=False):
        print("CIFAR-10!")
        print("ID: ", self.cid, " numClients: ", n_clients, " nonIID:", non_iid)
        if non_iid:
            with open(f'data/CIFAR10/{n_clients}/idx_train_{self.cid}.pickle', 'rb') as handle:
                idx_train = pickle.load(handle)

            with open(f'data/CIFAR10/{n_clients}/idx_test_{self.cid}.pickle', 'rb') as handle:
                idx_test = pickle.load(handle)


            (x_train, y_train), (x_test, y_test) = tf.keras.datasets.cifar10.load_data()
            x_train, x_test = x_train/255.0, x_test/255.0

            x_train = x_train[idx_train]
            x_test  = x_test[idx_test]

            y_train = y_train[idx_train]
            y_test  = y_test[idx_test]
            
        else:
            (x_train, y_train), (x_test, y_test) = tf.keras.datasets.cifar10.load_data()
            x_train, x_test                      = x_train/255.0, x_test/255.0

        return x_train, y_train, x_test, y_test, 10


    def load_CIFAR100(self, n_clients, non_iid=False):
        print("CIFAR-100!")
        print("ID: ", self.cid, " numClients: ", n_clients, " nonIID:", non_iid)
        (x_train, y_train), (x_test, y_test) = tf.keras.datasets.cifar100.load_data()
        x_train, x_test                      = x_train/255.0, x_test/255.0
        return x_train, y_train, x_test, y_test, 100
        
        
        
        
    def load_Colisao_Federado(self, n_clients, non_iid=False):
        from imblearn.over_sampling import SMOTE
        from sklearn.preprocessing import StandardScaler
        
        print("🚗 Carregando Dataset de Colisão para Aprendizado Federado...")
        path = '/home/flexe/PyFlexe/data/colisao/resultados_com_1000.csv'
        df = pd.read_csv(path)

        # 1. Preprocessamento de Categorias e Status
        if 'Lane' in df.columns:
            df['Lane'] = df['Lane'].astype('category').cat.codes
        if 'Status' in df.columns:
            df['Status'] = df['Status'].replace({'Colisao': 2, 'colisao': 2, 'Risco': 1}).fillna(0).astype(int)
        
        FEATURES = ['Lane', 'Posicao X', 'Posicao Y', 'Velocidade', 'Aceleracao', 'Direcao', 'Distancia', 'Time Buffer']
        TIMESTEPS = 10
        N_AHEAD = 5 # Linhas à frente

        # 2. Escalonamento
        scaler = StandardScaler()
        X_scaled = scaler.fit_transform(df[FEATURES].values)
        
        # 3. SMOTE (Aplicado antes das sequências para balancear a base base)
        target_future = df['Status'].shift(-N_AHEAD).fillna(0).astype(int).values
        smote = SMOTE(random_state=42)
        X_bal, y_bal = smote.fit_resample(X_scaled, target_future)

        # 4. Criação de Sequências (Janelamento)
        def create_tf_sequences(data, target, window_size):
            X_seq, y_seq = [], []
            for i in range(len(data) - window_size):
                X_seq.append(data[i:(i + window_size)])
                y_seq.append(target[i])
            return np.array(X_seq, dtype=np.float32), np.array(y_seq, dtype=np.int64)

        X_final, y_final = create_tf_sequences(X_bal, y_bal, TIMESTEPS)

        # 5. Divisão Treino/Teste
        x_train, x_test, y_train, y_test = train_test_split(
            X_final, y_final, test_size=0.2, random_state=42, stratify=y_final
        )

        # 6. Lógica de Distribuição Federada
        if non_iid:
            try:
                # Tenta carregar índices pré-calculados se existirem
                with open(f'data/colisao/{n_clients}/idx_train_{self.cid}.pickle', 'rb') as h:
                    idx_train = pickle.load(h)
                with open(f'data/colisao/{n_clients}/idx_test_{self.cid}.pickle', 'rb') as h:
                    idx_test = pickle.load(h)
                x_train, y_train = x_train[idx_train], y_train[idx_train]
                x_test, y_test = x_test[idx_test], y_test[idx_test]
            except:
                # Se não houver índices, divide os dados balanceados entre os clientes
                size_train = len(x_train) // n_clients
                size_test = len(x_test) // n_clients
                start_tr, end_tr = self.cid * size_train, (self.cid + 1) * size_train
                start_te, end_te = self.cid * size_test, (self.cid + 1) * size_test
                x_train, y_train = x_train[start_tr:end_tr], y_train[start_tr:end_tr]
                x_test, y_test = x_test[start_te:end_te], y_test[start_te:end_te]

        return x_train, y_train, x_test, y_test, 3 # 3 Classes: Seguro, Risco, Colisão
        
        

    
    
    def load_SIGN(self, n_clients, non_iid=False):
        print("SIGN!")
        print("ID: ", self.cid, " numClients: ", n_clients, " nonIID:", non_iid)
        # Assigning Path for Dataset
        data_dir = 'data/gtsrb-german-traffic-sign'
        train_path = 'data/gtsrb-german-traffic-sign/Train'
        test_path = 'data/gtsrb-german-traffic-sign/'
        IMG_HEIGHT = 30
        IMG_WIDTH = 30
        channels = 3
        
        # Finding Total Classes
        NUM_CATEGORIES = len(os.listdir(train_path))

        # Collecting the Training Data
        image_data = []
        image_labels = []
        for i in range(NUM_CATEGORIES):
            path = data_dir + '/Train/' + str(i)
            images = os.listdir(path)
            for img in images:
                try:
                    image = cv2.imread(path + '/' + img)
                    image_fromarray = Image.fromarray(image, 'RGB')
                    resize_image = image_fromarray.resize((IMG_HEIGHT, IMG_WIDTH))
                    image_data.append(np.array(resize_image))
                    image_labels.append(i)
                except:
                    print("Error in " + img)
        
        # Changing the list to numpy array
        image_data = np.array(image_data)
        image_labels = np.array(image_labels)
        
        # Shuffling the training data
        shuffle_indexes = np.arange(image_data.shape[0])
        np.random.shuffle(shuffle_indexes)
        image_data = image_data[shuffle_indexes]
        image_labels = image_labels[shuffle_indexes]
        
        # Splitting the data into train and validation set
        x_train, x_test, y_train, y_test = train_test_split(image_data, image_labels, test_size=0.3, random_state=42, shuffle=True)
        x_train = x_train/255 
        x_test = x_test/255
        
        #One hot encoding the labels
        y_train = tf.keras.utils.to_categorical(y_train, NUM_CATEGORIES)
        y_test = tf.keras.utils.to_categorical(y_test, NUM_CATEGORIES)
        
        if non_iid:
            with open(f'data/SIGN/{n_clients}/idx_train_{self.cid}.pickle', 'rb') as handle:
                idx_train = pickle.load(handle)

            with open(f'data/SIGN/{n_clients}/idx_test_{self.cid}.pickle', 'rb') as handle:
                idx_test = pickle.load(handle)
                
            x_train = x_train[idx_train]
            x_test  = x_test[idx_test]

            y_train = y_train[idx_train]
            y_test  = y_test[idx_test]
        
        return x_train, y_train, x_test, y_test, 43


    def slipt_dataset(self, x_train, y_train, x_test, y_test, n_clients):
        p_train = int(len(x_train)/n_clients)
        p_test  = int(len(x_test)/n_clients)

        selected_train = random.sample(range(len(x_train)), p_train)
        selected_test  = random.sample(range(len(x_test)), p_test)
        
        x_train  = x_train[selected_train]
        y_train  = y_train[selected_train]

        x_test   = x_test[selected_test]
        y_test   = y_test[selected_test]


        return x_train, y_train, x_test, y_test

    def dataset_percent(self, dataset_name, percent, label):
        if dataset_name == 'MNIST':
            with open(f'data/MNIST/%{percent}%/idx_train_{label}.pickle', 'rb') as handle:
                idx_train = pickle.load(handle)
            (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
            x_train, x_test = x_train/255.0, x_test/255.0
            x_train = x_train[idx_train]
            y_train = y_train[idx_train]
                            
            return x_train, y_train

    def select_dataset(self, dataset_name, n_clients, non_iid):
    
        if dataset_name == 'ColisaoFederada':
                     return self.load_Colisao_Federado(n_clients, non_iid)
                     
        elif dataset_name == 'MNIST':
            return self.load_MNIST(n_clients, non_iid)

        elif dataset_name == 'CIFAR100':
            return self.load_CIFAR100(n_clients, non_iid)

        elif dataset_name == 'CIFAR10':
            return self.load_CIFAR10(n_clients, non_iid)

        elif dataset_name == 'Motion-Sense':
            return self.load_MotionSense(n_clients, non_iid)

        elif dataset_name == 'UCI-HAR':
            return self.load_UCIHAR(n_clients, non_iid)
            
        elif dataset_name == 'FMNIST':
            return self.load_FMNIST(n_clients, non_iid)
        
        elif dataset_name == 'SIGN':
            return self.load_SIGN(n_clients, non_iid)
            
        elif dataset_name == 'Argoverse2':
            return self.load_Argoverse2(n_clients, non_iid)

        elif dataset_name == 'CORL2017':
            return self.load_CORL2017(n_clients, non_iid)


    def normalize_data(self, x_train, x_test):
        x_train = Normalizer().fit_transform(np.array(x_train))
        x_test  = Normalizer().fit_transform(np.array(x_test))
        return x_train, x_test
    
