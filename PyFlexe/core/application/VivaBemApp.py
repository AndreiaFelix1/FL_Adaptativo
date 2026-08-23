import core.proto.flexe_pb2 as flexe_pb2
import core.proto.flexe_pb2_grpc as flexe_pb2_grpc
import math
import os
import gc
from scipy.stats import entropy
import numpy as np
from math import log, e

# Make TensorFlow log less verbose
os.environ["TF_CPP_MIN_LOG_LEVEL"] = "3"

import tensorflow as tf
from sklearn.metrics import balanced_accuracy_score, cohen_kappa_score, confusion_matrix

from core.server.common.parameter import ndarrays_to_parameters, parameters_to_ndarrays, bytes_to_ndarray, ndarray_to_bytes
from core.server.common.aggregate import aggregate, aggregate_asynchronous, aggregate_asynchronous_alpha
from core.dataset.dataset_utils_tf import ManageDatasets
from core.model.model_definition_tf import ModelCreation
from glob import glob

#TODO: Run only with Global models (Allan's idea) Do not create models for clients.

def entropy_bits(labels, base=None):
    value,counts = np.unique(labels, return_counts=True)
    return entropy(counts, base=base)

def balanced_accuracy_kappa(model, test_x, test_y, LIMIAR_PROB=0.5):
    y_pred = model.predict(test_x, batch_size=32, verbose=0)
    print("test_y: ", test_y)
    print("y_pred ANTES: ", y_pred)
    y_pred = np.argmax(y_pred, axis=1)
    print("y_pred DEPOIS: ", y_pred)
    #acc_blcd = balanced_accuracy_score(test_y, y_pred > LIMIAR_PROB)
    #kappa = cohen_kappa_score(test_y, y_pred > LIMIAR_PROB)
    #return acc_blcd, kappa

class VivaBemApp(flexe_pb2_grpc.FlexeServicer):
    def __init__(self):
        self.device = tf.device("cuda:0" if tf.test.is_gpu_available() else "cpu")
        print("Num GPUs Available: ", len(tf.config.list_physical_devices('GPU')))
        self.strategy = "FED_AVG"
        self.directory = "./results/"

    #Server Functions
    def center_fit(self, request, context): #GenericRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - CENTER_FIT",
            " idEntity: ", request.idEntity, 
            " model: ", request.model, 
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel: ", request.idModel,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(0).select_dataset(dataset_name=request.dataset, n_clients=1, non_iid=False) #All Data

        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=-1.0,
            entropy=-1.0,
            loss=-1.0,
            accuracy=-1.0,
            msg="NULL"
        )

    def center_evaluate(self, request, context): #GenericRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - CENTER_EVALUATE",
            " idEntity: ", request.idEntity, 
            " model: ", request.model, 
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel: ", request.idModel,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(0).select_dataset(dataset_name=request.dataset, n_clients=1, non_iid=False) #All Data

        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=-1.0,
            entropy=-1.0,
            loss=-1.0,
            accuracy=-1.0,
            msg="NULL"
        )

    def set_strategy(self, request, context): #GenericRequest -> GenericReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - SET_STRATEGY",
            " idEntity: ", request.idEntity, 
            " model: ", request.model, 
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel: ", request.idModel,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY

        self.strategy = request.msg

        print("\n\n")
        return flexe_pb2.GenericReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            reply=0, 
            msg=self.strategy
        )


    def get_strategy(self, request, context): #GenericRequest -> GenericReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - GET_STRATEGY",
            " idEntity: ", request.idEntity, 
            " model: ", request.model, 
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel: ", request.idModel,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY

        print("\n\n")
        return flexe_pb2.GenericReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            reply=0, 
            msg=self.strategy
        )


    def end(self, request, context): #GenericRequest -> GenericReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - END",
            " idEntity: ", request.idEntity, 
            " model: ", request.model, 
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel: ", request.idModel,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY

        models = glob(self.directory+"*.h5")
        for model in models:
            os.remove(model)
        tf.keras.backend.clear_session()
        gc.collect()

        print("\n\n")
        return flexe_pb2.GenericReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            reply=0, 
            msg="NULL"
        )

    def initialize_parameters(self, request, context): #TTRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - INITIALIZE_PARAMETERS", 
            " SERVER: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " trainFlag: ", request.trainFlag, 
            " epochs: ", request.epochs,
            " batch: ", request.batch, 
            " numClients: ", request.numClients,
            " percentDataset: ", request.percentDataset,
            " models: ", request.models,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY

        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(0).select_dataset(dataset_name=request.dataset, n_clients=1, non_iid=False) #All Data
        initial_path = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idEntity) + "_" + str(request.seed) +"_initial.h5"
        global_path = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idEntity) + "_" + str(request.seed) + "_global.h5"
        numExamples = len(x_train)
        accuracy = -1.0
        loss = -1.0
        modelSize = -1
        entropy = entropy_bits(y_train)
        model = []

        print("Initial File Name: ", initial_path)
        print("Global File Name: ", global_path)

        if request.trainFlag:
            # CREATE INITIALIZE MODEL PROCESS
            if "DNN_MODEL" in request.model:
                print("DNN!")
                model = ModelCreation().create_DNN(x_train.shape, num_classes)
            elif "CNN_MODEL" in request.model:
                print("CNN!")
                model = ModelCreation().create_CNN(x_train.shape, num_classes)
            elif "VGG_MODEL" in request.model:
                print("VGG!")
                model = ModelCreation().create_VGG(x_train.shape, num_classes)
            elif "CNN_SIGN" in request.model:
                print("CNN_SIGN!")
                model = ModelCreation().create_CNN_SIGN(x_train.shape, num_classes)
            elif "MOBILENET_V1" in request.model:
                print("MobileNet V1!")
                model = ModelCreation().create_MobileNet(x_train.shape, num_classes)
            elif "RESNET_50" in request.model:
                print("ResNet 50!")
                model = ModelCreation().create_ResNet(x_train.shape, num_classes)
            elif "EFFICIENTNET_B0" in request.model:
                print("EfficientNet B0!")
                model = ModelCreation().create_EfficientNet(x_train.shape, num_classes)
            elif "GENERIC_MODEL" in request.model:
                print("Generic Model!")
                model = ModelCreation().create_generic_model(x_train.shape, num_classes)
            
            history = model.fit(x_train, y_train, epochs=request.epochs, batch_size=request.batch)
            print("Metrics: ", history.history)
            model.save(global_path)
            model.save(initial_path)
            accuracy = history.history["accuracy"][0]
            loss = history.history["loss"][0]

            try:
                modelSize = os.path.getsize(initial_path)*8 #Model size in bits
            except OSError:
                print("Path '%s' does not exists or is inaccessible" % initial_path)

            print("INITIALIZE_PARAMETERS Tamanho do Modelo: ", modelSize)

            with open(initial_path.replace("h5", "txt"), 'a') as file_save:
                file_save.write("INITIALIZE_PARAMETERS: "+str(history.history)+"\n")
            # CREATE INITIALIZE MODEL PROCESS

        # CLEAN MEMORY
        tf.keras.backend.clear_session()
        del model
        del x_train
        del y_train
        del x_test
        del y_test
        del num_classes
        gc.collect() # Force Garbage Collect
        # CLEAN MEMORY

        print("\n\n")
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=numExamples,
            entropy=entropy,
            loss=loss,
            accuracy=accuracy,
            msg="modelSize="+str(modelSize)+";"
        )

    def aggregate_sync_fit(self, request, context): #AggregationRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - AGGREGATE_SEMISYNC_FIT", 
            " SERVER: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " numClients: ", request.numClients, 
            " numExamples: ", request.numExamples,
            " models: ", request.models, 
            " strategy: ", request.strategy,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=1, non_iid=False) #All Data
        numExamples = len(x_train)
        accuracy = -1.0
        loss = -1.0
        entropy = entropy_bits(y_train)
        list_models = []
        model = []
        weights_aggregated = []

        # LOAD AGG MODEL 
        global_path = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idEntity) + "_" + str(request.seed) + "_global.h5"
        print("Global File Name: ", global_path)
        model_agg = tf.keras.models.load_model(global_path)
        # LOAD AGG MODEL

        if self.strategy == "FED_AVG":
            client_IDs = request.models.split(";")
            client_EXs = request.numExamples.split(";")
            for client_ID, client_EX in zip(client_IDs, client_EXs):
                if client_ID.isdigit():
                    client_ID = int(client_ID)
                    numExamples = int(client_EX)
                    fileName = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(client_ID) + "_" + str(request.seed) + ".h5"
                    print("Client "+str(client_ID)+" File Name: ", fileName)
                    print("Client "+str(client_ID)+" Num Examples: ", numExamples)         
                    model = tf.keras.models.load_model(fileName)
                    tensors = model.get_weights()
                    list_models.append((tensors, numExamples))

            # MAKE AGGREGATION
            if len(list_models) != 0:
                weights_aggregated = aggregate(list_models)
                model_agg.set_weights(weights_aggregated)
            model_agg.save(global_path)
            # MAKE AGGREGATION

            data = model_agg.evaluate(x_train, y_train)
            history={}
            history["loss"] = [float(data[0])]
            history["accuracy"] = [float(data[1])]
            accuracy = float(data[1])
            loss = float(data[0])
            print("Metrics: ", history)

            with open(global_path.replace("h5", "txt"), 'a') as file_pi:
                file_pi.write("AGGREGATE_SEMISYNC_FIT: "+str(history)+"\n")
        else:
            pass
        
        # CLEAN MEMORY
        tf.keras.backend.clear_session()
        del weights_aggregated
        del list_models
        del model_agg
        del model
        del x_train
        del y_train
        del x_test
        del y_test
        del num_classes
        gc.collect()
        # CLEAN MEMORY

        print("\n\n")
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=numExamples,
            entropy=entropy,
            loss=loss,
            accuracy=accuracy,
            msg="NULL"
        )


    def aggregate_async_fit(self, request, context): #AggregationRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - AGGREGATE_ASYNC_FIT", 
            " SERVER: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " numClients: ", request.numClients, 
            " numExamples: ", request.numExamples,
            " models: ", request.models, 
            " strategy: ", request.strategy,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=1, non_iid=False) #All Data
        numExamples = len(x_train)
        accuracy = -1.0
        loss = -1.0
        entropy = entropy_bits(y_train)
        list_models = []
        model = []
        weights_aggregated = []
        model_agg = []

        if self.strategy == "FED_AVG":
            # LOAD MODEL
            fileName = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.models) + "_" + str(request.seed) + ".h5"
            model = tf.keras.models.load_model(fileName)
            # LOAD MODEL

            # WEIGHTS FROM MODEL
            tensors = model.get_weights()
            numExamples = int(request.numExamples)
            list_models.append((tensors, numExamples))
            # WEIGHTS FROM MODEL

            # LOAD AGG MODEL 
            global_path = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idEntity) + "_" + str(request.seed) + "_global.h5"
            print("Global File Name: ", global_path)
            model_agg = tf.keras.models.load_model(global_path)
            tensors_agg = model_agg.get_weights()
            list_models.append((tensors_agg, numExamples))
            # LOAD AGG MODEL 

            # MAKE AGGREGATION
            weights_aggregated = aggregate_asynchronous(list_models)
            model_agg.set_weights(weights_aggregated)
            model_agg.save(global_path)
            # MAKE AGGREGATION

            data = model_agg.evaluate(x_train, y_train)
            history={}
            history["loss"] = [float(data[0])]
            history["accuracy"] = [float(data[1])]
            print("Metrics: ", history)

            with open(fileName.replace("h5", "txt"), 'a') as file_pi:
                file_pi.write("AGGREGATE_ASYNC_FIT: "+str(history)+"\n")

            accuracy = float(data[0])
            loss = float(data[1])
        else:
            pass

        # CLEAN MEMORY
        tf.keras.backend.clear_session()
        del weights_aggregated
        del list_models
        del model_agg
        del model
        del x_train
        del y_train
        del x_test
        del y_test
        del num_classes
        gc.collect()
        # CLEAN MEMORY

        print("\n\n")
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=numExamples,
            entropy=entropy,
            loss=loss,
            accuracy=accuracy,
            msg="NULL"
        )

    def aggregate_evaluate(self, request, context): #AggregationRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - AGGREGATE_EVALUATE", 
            " SERVER: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " numClients: ", request.numClients, 
            " numExamples: ", request.numExamples,
            " models: ", request.models, 
            " strategy: ", request.strategy,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY

        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=1, non_iid=False) #All Data
        numExamples = len(x_train)
        accuracy = -1.0
        loss = -1.0
        entropy = entropy_bits(y_train)

        # LOAD MODEL
        global_path = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idEntity) + "_" + str(request.seed) + "_global.h5"
        print("Global File Name: ", global_path)
        isExist = os.path.exists(global_path)
        if isExist:
            model = tf.keras.models.load_model(global_path)
            data = model.evaluate(x_test, y_test)
            loss = float(data[0])
            accuracy = float(data[1])
            history={}
            history["loss"] = [loss]
            history["accuracy"] = [accuracy]
            with open(global_path.replace("h5", "txt"), 'a') as file_save:
                file_save.write("AGGREGATE_EVALUATE: "+str(history)+"\n")
        else:
            print("\n\n!!!SERVER - AGGREGATE_EVALUATE (VOID_MODEL)!!!\n\n")
            model = []
        # LOAD MODEL

        # CLEAN MEMORY
        tf.keras.backend.clear_session()
        del model
        del x_train
        del y_train
        del x_test
        del y_test
        del num_classes
        gc.collect()
        # CLEAN MEMORY

        print("\n\n")
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=numExamples,
            entropy=entropy,
            loss=loss,
            accuracy=accuracy,
            msg="NULL"
        )

    #Client Functions 
    def fit(self, request, context): #TTRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "CLIENT - FIT", 
            " CLIENT: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " trainFlag: ", request.trainFlag, 
            " epochs: ", request.epochs,
            " batch: ", request.batch, 
            " numClients: ", request.numClients,
            " percentDataset: ", request.percentDataset,
            " models: ", request.models,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        if request.trainFlag:
            os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=request.numClients, non_iid=request.nonIID)
        numExamples = len(x_train)
        accuracy = -1.0
        loss = -1.0
        modelSize = -1
        entropy = entropy_bits(y_train)
        print("Entropy Bits: ", entropy)

        if request.trainFlag:
            fileName = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idEntity) + "_" + str(request.seed) + ".h5"
            print("Local File Name: ", fileName)
            isExist = os.path.exists(fileName)
            if isExist:
                model = tf.keras.models.load_model(fileName)
            else:
                initial_path = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idModel) + "_" + str(request.seed) +"_initial.h5"
                print("Initial File Name: ", initial_path)
                model = tf.keras.models.load_model(initial_path)

            history = model.fit(x_train, y_train, epochs=request.epochs, batch_size=request.batch)
            print("Metrics: ", history.history)
            accuracy = history.history["accuracy"][0]
            loss = history.history["loss"][0]
            model.save(fileName)
            try:
                modelSize = os.path.getsize(fileName)*8 #Model size in bits
            except OSError:
                print("Path '%s' does not exists or is inaccessible" % fileName)
       
            with open(fileName.replace("h5", "txt"), 'a') as file_save:
                file_save.write("FIT: "+str(history.history)+"\n")

            tf.keras.backend.clear_session()
            del model 
            gc.collect()           

        # CLEAN MEMORY
        del x_train
        del y_train
        del x_test
        del y_test
        del num_classes            
        # CLEAN MEMORY
        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=numExamples,
            entropy=entropy,
            loss=loss,
            accuracy=accuracy,
            msg="modelSize="+str(modelSize)+";"
        )

    def evaluate(self, request, context): #TTRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "CLIENT - EVALUATE", 
            " CLIENT: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " trainFlag: ", request.trainFlag, 
            " epochs: ", request.epochs,
            " batch: ", request.batch, 
            " numClients: ", request.numClients,
            " percentDataset: ", request.percentDataset,
            " models: ", request.models,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=request.numClients, non_iid=request.nonIID)
        numExamples = len(x_train)
        accuracy = -1.0
        loss = -1.0
        entropy = entropy_bits(y_train)

        # LOAD MODEL
        fileName = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idEntity) + "_" + str(request.seed) + ".h5"
        print("Local File Name: ", fileName)
        model = tf.keras.models.load_model(fileName)
        # LOAD MODEL

        data = model.evaluate(x_test, y_test)
        #acc_blcd, kappa = balanced_accuracy_kappa(model, x_test, y_test, LIMIAR_PROB=0.5)
        history={}
        history["loss"] = [float(data[0])]
        history["accuracy"] = [float(data[1])]
        #history["accuracy_blcd"] = [acc_blcd]
        #history["kappa"] = [kappa]
        accuracy = float(data[1])
        loss = float(data[0])
        with open(fileName.replace("h5", "txt"), 'a') as file_save:
            file_save.write("EVALUATE: "+str(history)+"\n")

        # CLEAN MEMORY
        tf.keras.backend.clear_session()
        del model
        del x_train
        del y_train
        del x_test
        del y_test
        del num_classes
        gc.collect()
        # CLEAN MEMORY     
        
        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=numExamples,
            entropy=entropy,
            loss=loss,
            accuracy=accuracy,
            msg="NULL"
        )

    def update_model(self, request, context): #TTRequest -> ModelReply #Colocar aqui o FedPredict, Pegar informações(Args): (Rodada Atual, Número de Rodadas Totais), Quantidade de Rodadas sem treinar(Model Version), Similaridade dos Contextos (Valor de 0-1) 
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "CLIENT - UPDATE_MODEL", 
            " CLIENT: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " trainFlag: ", request.trainFlag, 
            " epochs: ", request.epochs,
            " batch: ", request.batch, 
            " numClients: ", request.numClients,
            " percentDataset: ", request.percentDataset,
            " models: ", request.models,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=request.numClients, non_iid=request.nonIID)
        numExamples = len(x_train)
        accuracy = -1.0
        loss = -1.0
        entropy = entropy_bits(y_train)

        fileName = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idEntity) + "_" + str(request.seed) + ".h5"
        print("Local File Name: ", fileName)
        global_path = self.directory + str(request.dataset) + "_" + str(request.model) + "_" + str(request.scenario) + "_" + str(request.idModel) + "_" + str(request.seed) + "_global.h5"
        print("Global File Name: ", global_path)
        model = tf.keras.models.load_model(global_path)
        model.save(fileName)

        data = model.evaluate(x_test, y_test)
        history={}
        history["loss"] = [float(data[0])]
        history["accuracy"] = [float(data[1])]
        accuracy = float(data[1])
        loss = float(data[0])
        with open(fileName.replace("h5", "txt"), 'a') as file_save:
            file_save.write("UPDATE_EVAL: "+str(history)+"\n")

        # CLEAN MEMORY
        tf.keras.backend.clear_session()
        del model
        del x_train
        del y_train
        del x_test
        del y_test
        del num_classes
        gc.collect()
        # CLEAN MEMORY

        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=numExamples,
            entropy=entropy,
            loss=loss,
            accuracy=accuracy,
            msg="NULL"
        )

    def get_information(self, request, context): #GenericRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "CLIENT - GET_INFORMATION",
            " idEntity: ", request.idEntity, 
            " model: ", request.model, 
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel: ", request.idModel,
            " msg: ", request.msg
        )

        x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=request.numClients, non_iid=request.nonIID)
        numExamples = len(x_train)
        entropy = entropy_bits(y_train)
        
        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=numExamples,
            entropy=entropy,
            loss=-1.0,
            accuracy=-1.0,
            msg="NULL"
        )

    def set_information(self, request, context): #GenericRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "CLIENT - SET_INFORMATION",
            " idEntity: ", request.idEntity, 
            " model: ", request.model, 
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel: ", request.idModel,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        #x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=request.numClients, non_iid=request.nonIID)
        
        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=-1.0,
            entropy=-1.0,
            loss=-1.0,
            accuracy=-1.0,
            msg="NULL"
        )

    def aggregate_client(self, request, context): #TTRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - AGGREGATE_CLIENT", 
            " SERVER: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " trainFlag: ", request.trainFlag, 
            " epochs: ", request.epochs,
            " batch: ", request.batch, 
            " numClients: ", request.numClients,
            " percentDataset: ", request.percentDataset,
            " models: ", request.models,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        #x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=request.numClients, non_iid=request.nonIID)
        
        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=-1.0,
            entropy=-1.0,
            loss=-1.0,
            accuracy=-1.0,
            msg="NULL"
        )

    def fit_all(self, request, context): #TTRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - FIT_ALL", 
            " SERVER: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " trainFlag: ", request.trainFlag, 
            " epochs: ", request.epochs,
            " batch: ", request.batch, 
            " numClients: ", request.numClients,
            " percentDataset: ", request.percentDataset,
            " models: ", request.models,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        #x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=request.numClients, non_iid=request.nonIID)
        
        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=-1.0,
            entropy=-1.0,
            loss=-1.0,
            accuracy=-1.0,
            msg="NULL"
        )

    def evaluate_all(self, request, context): #TTRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - EVALUATE_ALL", 
            " SERVER: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " trainFlag: ", request.trainFlag, 
            " epochs: ", request.epochs,
            " batch: ", request.batch, 
            " numClients: ", request.numClients,
            " percentDataset: ", request.percentDataset,
            " models: ", request.models,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        #x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=request.numClients, non_iid=request.nonIID)
        
        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=-1.0,
            entropy=-1.0,
            loss=-1.0,
            accuracy=-1.0,
            msg="NULL"
        )

    def update_all(self, request, context): #TTRequest -> ModelReply
        request.idEntity = request.idEntity - 1
        request.idModel = request.idModel - 1
        print(
            "SERVER - UPDATE_ALL", 
            " SERVER: ", request.idEntity, 
            " model: ", request.model,
            " dataset: ", request.dataset,
            " scenario: ", request.scenario,
            " seed: ", request.seed,
            " nonIID: ", request.nonIID,
            " idModel:", request.idModel, 
            " trainFlag: ", request.trainFlag, 
            " epochs: ", request.epochs,
            " batch: ", request.batch, 
            " numClients: ", request.numClients,
            " percentDataset: ", request.percentDataset,
            " models: ", request.models,
            " msg: ", request.msg
        )
        # OUTPUT DIRECTORY
        if request.nonIID:
            self.directory = "./results/"+"NIID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"
        else:
            self.directory = "./results/"+"IID"+"-"+str(request.dataset)+"-"+str(request.model)+"-"+str(request.scenario)+"-"+str(request.seed)+"/"

        os.makedirs(self.directory, exist_ok=True)
        # OUTPUT DIRECTORY
        #x_train, y_train, x_test, y_test, num_classes = ManageDatasets(request.idEntity).select_dataset(dataset_name=request.dataset, n_clients=request.numClients, non_iid=request.nonIID)

        print("\n\n") 
        return flexe_pb2.ModelReply(
            idEntity=request.idEntity,
            model=request.model,
            dataset=request.dataset,
            scenario=request.scenario,
            seed=request.seed,
            nonIID=request.nonIID,
            idModel=request.idModel, 
            numExamples=-1.0,
            entropy=-1.0,
            loss=-1.0,
            accuracy=-1.0,
            msg="NULL"
        )