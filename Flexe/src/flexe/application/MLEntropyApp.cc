#include "MLEntropyApp.h"

using namespace veins;
using namespace flexe;

Define_Module(MLEntropyApp);

void MLEntropyApp::initialize(int stage){
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        self = getParentModule()->getIndex();
        
        epochs = par("epochs").intValue();
        batch = par("batch").intValue();
        speedZero = par("speedZero").boolValue();
        computationCapability = par("computationCapability").doubleValue();
        computationCapability = computationCapability*(pow(10, 9));
        datasetVector = cStringTokenizer(par("dataset")).asVector();
        numClients = par("numClients").intValue();

        address = par("address").stringValue();

        datasetUsedUpdateMetric = registerSignal("datasetUsedUpdate");
        datasetTrainUpdateMetric = registerSignal("datasetUsedTrain");
        datasetEvaluateUpdateMetric = registerSignal("datasetUsedEvaluate");
        trainLatencyMetric = registerSignal("trainLatency");
        compCapabilityMetric = registerSignal("compCapability");
        lossTrainMetric = registerSignal("lossTrain");
        accuracyTrainMetric = registerSignal("accuracyTrain");
        lossEvaluateMetric = registerSignal("lossEvaluate");
        accuracyEvaluateMetric = registerSignal("accuracyEvaluate");
        lossUpdateMetric = registerSignal("lossUpdate");
        accuracyUpdateMetric = registerSignal("accuracyUpdate");

        dataset2Number["MNIST"] = 1;
        dataset2Number["FMNIST"] = 2;
        dataset2Number["CIFAR10"] = 3;

        emit(compCapabilityMetric, (double)computationCapability);
    }
    else if (stage == 1) {
        chArgs.SetMaxReceiveMessageSize(-1);
        chArgs.SetMaxSendMessageSize(-1);
        chArgs.SetGrpclbFallbackTimeout(7200000);
        client = new FlexeClient(grpc::CreateCustomChannel(address, grpc::InsecureChannelCredentials(), chArgs));
        for(std::vector<std::string>::iterator it  = datasetVector.begin(); it != datasetVector.end(); it++){
            dataset = *it;
            std::tie(numExamples, entropy, lossModel, accuracyModel, outputMSG) = client->fit(self, "NULL", dataset, "NULL", -777, true, -777, false, -777, -777, numClients, -1.0, "NULL", "NULL");
            ////std::cout << self << " - Dataset: " << dataset << " Entropy: " << entropy  << " Num. Examples: " << numExamples << endl;
            datasetEntropyMap.insert(std::make_pair(dataset, std::make_tuple(entropy, numExamples)));
        }
        dataset = "NULL";
        computationRequirement = -1;
        modelVersion = -1;
        accuracyModel = -1;
        lossModel = -1;
        numExamples = -1;
        entropy = -1;
    }
}

MLEntropyApp::~MLEntropyApp(){
    cancelAndDelete(trainLocalModelEvt);
    cancelAndDelete(sendResourceRequestEvt);
    delete client;
}

void MLEntropyApp::finish(){
    DemoBaseApplLayer::finish();
}

void MLEntropyApp::onBSM(DemoSafetyMessage* bsm){
    switch(bsm->getKind()){
    case SEND_BEACON_EVT:{
        break;
    }
    default:{
        //std::cout << self << " - (onBSM) The message type was not detected. " << bsm->getKind() << endl;
        //std::cout << "\n" << endl;
        break;
    }
    }
}

void MLEntropyApp::onWSM(BaseFrame1609_4* wsm){
    switch(wsm->getKind()){
    case SEND_GLOBAL_MODEL_EVT:{
        //std::cout << self << " - (VEH|onWSM) SEND_GLOBAL_MODEL_EVT " << simTime().dbl() << endl;
        FlexeMessage* flexe_msg = check_and_cast<FlexeMessage*>(wsm);
        //std::cout << self << " - (VEH|onWSM) Selected Clients: " << flexe_msg->getClientSelection() << endl;
        std::vector<std::string> selectedClientsVector = client->splitSTR(flexe_msg->getClientSelection(), ';');
        trainFlag = false;

        for(std::vector<std::string>::iterator it  = selectedClientsVector.begin(); it != selectedClientsVector.end(); it++){
            if(std::to_string(self) == *it){
                //std::cout << self << " - (VEH|onWSM) " << self << " == "<< *it << endl;
                trainFlag = true;
                break;
            }
        }

        if(trainFlag == true){
            model = flexe_msg->getModel();
            dataset = flexe_msg->getDataset();
            scenario = flexe_msg->getScenario();
            seed = flexe_msg->getSeed();
            nonIID = flexe_msg->getNonIID();
            idModel = flexe_msg->getIdModel();
            numClients = flexe_msg->getNumClients();
            percentDataset = flexe_msg->getPercentDataset();
            modelVersion = flexe_msg->getModelVersion();
            computationRequirement = flexe_msg->getComputationRequirement();
            colorDataset = flexe_msg->getColor();
            dynamicEpoch = flexe_msg->getDynamicEpoch();
            roundDeadline = flexe_msg->getRoundDeadline();
            //std::cout << self << " Change Color to: " << colorDataset.c_str() << endl;
            findHost()->getDisplayString().setTagArg("i", 1, colorDataset.c_str());
            scheduleAt(simTime().dbl(), trainLocalModelEvt);
        }else{ 
            std::tie(numExamples, entropy, lossModel, accuracyModel, outputMSG) = client->update_model(self, flexe_msg->getModel(), flexe_msg->getDataset(), flexe_msg->getScenario(), flexe_msg->getSeed(), flexe_msg->getNonIID(), flexe_msg->getIdModel(), trainFlag, epochs, batch, flexe_msg->getNumClients(), flexe_msg->getPercentDataset(), "", "");
            emit(datasetUsedUpdateMetric, dataset2Number[flexe_msg->getDataset()]);
            emit(lossUpdateMetric, (double)lossModel);
            emit(accuracyUpdateMetric, (double)accuracyModel);           
            //std::cout << self << " - (VEH|handleSelfMsg) Update Accuracy: " << accuracyModel << " Loss: " << lossModel << " N. Examples: " << numExamples << endl;
        }
        //std::cout << "\n" << endl;

        //CLEAR DATA STRUCTURES
        selectedClientsVector.clear();
        //CLEAR DATA STRUCTURES
        break;
    }
    case SEND_LOCAL_MODEL_EVT:{
        break;
    }
    case RESOURCE_REQUEST_EVT:{
        //std::cout << self << " - (VEH|onWSM) RESOURCE_REQUEST_EVT " << simTime().dbl() << endl;
        FlexeMessage* flexe_msg = check_and_cast<FlexeMessage*>(wsm);
        std::vector<std::string> clientResourceVector = client->splitSTR(flexe_msg->getClientSelection(), ';');
        resourceFlag = false;
        for(std::vector<std::string>::iterator it  = clientResourceVector.begin(); it != clientResourceVector.end(); it++){
            if(std::to_string(self) == *it){
                //std::cout << self << " - (VEH|onWSM) " << self << " == "<< *it << endl;
                resourceFlag = true;
                break;
            }
        }
        if(resourceFlag == true){
            scheduleAt(simTime().dbl(), sendResourceRequestEvt);
        }
        //CLEAR DATA STRUCTURES
        clientResourceVector.clear();
        //CLEAR DATA STRUCTURES
        break;
    }
    default:{
        //std::cout << self << " - (onWSM) The message type was not detected. " << wsm->getKind() << endl;
        //std::cout << "\n" << endl;
        break;
    }
    }
}

void MLEntropyApp::onWSA(DemoServiceAdvertisment* wsa){
}

void MLEntropyApp::handleSelfMsg(cMessage* msg){
    switch (msg->getKind()) {
        case SEND_BEACON_EVT:{
            //std::cout << self << " - (VEH|handleSelfMsg) SEND_BEACON_EVT " << simTime().dbl() << endl;
            DemoSafetyMessage* bsm = new DemoSafetyMessage();
            populateWSM(bsm);
            std::string sendID = traciVehicle->getVehicleId() + ";" + std::to_string(self);
            bsm->setName(sendID.c_str());
            bsm->setSpeed(traciVehicle->getSpeed());
            bsm->setModelVersion(modelVersion);
            bsm->setComputationCapability(computationCapability);
            bsm->setLocalEpochs(epochs);
            std::string numExamplesBeacon = "";
            std::string EntropyBeacon = "";
            for(std::map<std::string, std::tuple<double, int>>::iterator it  = datasetEntropyMap.begin(); it != datasetEntropyMap.end(); it++){
                //std::cout << simTime().dbl() << " - Dataset: " << it->first << " Entropy: " << std::get<0>(it->second) << " NumExamples: " << std::get<1>(it->second) << endl;
                EntropyBeacon = (it->first+":"+std::to_string(std::get<0>(it->second))) + ";" + EntropyBeacon;
                numExamplesBeacon = (it->first+":"+std::to_string(std::get<1>(it->second))) + ";" + numExamplesBeacon;
            }
            //std::cout << "EntropyBeacon: " << EntropyBeacon << endl;
            //std::cout << "numExamplesBeacon: " << numExamplesBeacon << endl;
            bsm->setNumExamples(numExamplesBeacon.c_str());
            bsm->setEntropyExamples(EntropyBeacon.c_str());
            sendDown(bsm);
            scheduleAt(simTime() + beaconInterval, sendBeaconEvt);
            //std::cout << "\n" << endl;
            break;
        }

        case TRAIN_LOCAL_MODEL_EVT:{
            //std::cout << self << " - (VEH|handleSelfMsg) TRAIN_LOCAL_MODEL_EVT " << simTime().dbl() << endl;
            if(dynamicEpoch){
                epochs=1;
                std::tie(numExamples, entropy, lossModel, accuracyModel, outputMSG) = client->fit(self, model, dataset, scenario, seed, nonIID, idModel, trainFlag, epochs, batch, numClients, percentDataset, "", ""); //Run only once to data colect
                epochs = std::floor((roundDeadline*computationCapability)/(double(numExamples)* computationRequirement));
                epochs = epochs - 1;
                if(epochs <= 0){
                    epochs = 1;
                }
                std::tie(numExamples, entropy, lossModel, accuracyModel, outputMSG) = client->fit(self, model, dataset, scenario, seed, nonIID, idModel, trainFlag, epochs, batch, numClients, percentDataset, "", "dynamicEpoch");
                epochs = std::stoi(client->splitSTR(client->splitSTR(outputMSG, ';')[1], '=')[1]);
            }else{
                epochs = par("epochs").intValue();
                std::tie(numExamples, entropy, lossModel, accuracyModel, outputMSG) = client->fit(self, model, dataset, scenario, seed, nonIID, idModel, trainFlag, epochs, batch, numClients, percentDataset, "", "");
            }

            modelSize = std::stod(client->splitSTR(client->splitSTR(outputMSG, ';')[0], '=')[1]);

            emit(datasetTrainUpdateMetric, dataset2Number[dataset.c_str()]);
            emit(lossTrainMetric, (double)lossModel);
            emit(accuracyTrainMetric, (double)accuracyModel);
            //std::cout << self << " - (VEH|handleSelfMsg) Training Accuracy: " << accuracyModel << " Loss: " << lossModel << " N. Examples: " << numExamples << " seed: " << seed << " dataset: " << dataset << " model: " << model << endl;

            std::tie(numExamples, entropy, lossModel, accuracyModel, outputMSG) = client->evaluate(self, model, dataset, scenario, seed, nonIID, idModel, trainFlag, epochs, batch, numClients, percentDataset, "", "");
            emit(datasetEvaluateUpdateMetric, dataset2Number[dataset.c_str()]);
            emit(lossEvaluateMetric, (double)lossModel);
            emit(accuracyEvaluateMetric, (double)accuracyModel);           
            //std::cout << self << " - (VEH|handleSelfMsg) Evaluation Accuracy: " << accuracyModel << " Loss: " << lossModel << " N. Examples: " << numExamples << " seed: " << seed << " dataset: " << dataset << " model: " << model << endl;
            
            trainingLatency = ((double(numExamples)* computationRequirement)/computationCapability) * epochs;
            std::cout << self << " - (VEH|handleSelfMsg) Evaluation Accuracy: " << accuracyModel << " Loss: " << lossModel << " N. Examples: " << numExamples << " seed: " << seed << " dataset: " << dataset << " model: " << model << " trainingLatency: " << trainingLatency << endl;
            emit(trainLatencyMetric, (double)trainingLatency);
            if(dynamicEpoch){
                trainingLatency = trainingLatency + uniform(0, 0.01);
            }

            //SEND_LOCAL_MODEL
            FlexeMessage* flexe_msg = new FlexeMessage();
            DemoBaseApplLayer::populateWSM(flexe_msg);
            flexe_msg->setKind(SEND_LOCAL_MODEL_EVT);
            flexe_msg->setSenderID(self);
            flexe_msg->setModel(model.c_str());
            flexe_msg->setDataset(dataset.c_str());
            flexe_msg->setScenario(scenario.c_str());
            flexe_msg->setSeed(seed);
            flexe_msg->setNonIID(nonIID);
            flexe_msg->setNumExamples(numExamples);
            flexe_msg->setIdModel(idModel);
            flexe_msg->setModelVersion(modelVersion);
            flexe_msg->setLoss(lossModel);
            flexe_msg->setAccuracy(accuracyModel);
            flexe_msg->setComputationCapability(computationCapability);
            flexe_msg->setEntropy(entropy);
            DemoBaseApplLayer::sendDelayedDown(flexe_msg, trainingLatency);
            //SEND_LOCAL_MODEL

            trainFlag = false;
            //std::cout << "\n" << endl;
            break;
        }
        case RESOURCE_REQUEST_EVT:{
            //std::cout << self << " - (VEH|handleSelfMsg) RESOURCE_REQUEST_EVT " << simTime().dbl() << endl;
            std::tie(numExamples, entropy, lossModel, accuracyModel, outputMSG) = client->get_information(self, model, dataset, scenario, seed, nonIID, idModel, "");
            
            FlexeMessage* flexe_msg = new FlexeMessage();
            DemoBaseApplLayer::populateWSM(flexe_msg);
            flexe_msg->setKind(RESOURCE_REQUEST_EVT);
            flexe_msg->setSenderID(self);
            flexe_msg->setNumExamples(numExamples);
            flexe_msg->setComputationCapability(computationCapability);
            flexe_msg->setEntropy(entropy);
            DemoBaseApplLayer::sendDelayedDown(flexe_msg, uniform(0, 0.01));

            resourceFlag = false;
            //std::cout << "\n" << endl;
            break;
        }
        default: {
            //std::cout << self << " handleSelfMsg - The message type was not detected. " << msg->getKind() << endl;
            break;
        }
    }
}

void MLEntropyApp::handlePositionUpdate(cObject* obj){
    if(speedZero){
        traciVehicle->setSpeed(0.0);
    }
    DemoBaseApplLayer::handlePositionUpdate(obj);
}
