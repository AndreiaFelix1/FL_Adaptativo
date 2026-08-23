#Número de clientes por tempo/round
from matplotlib import pyplot as plt
from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes, mark_inset
import numpy as np
from glob import glob
import statistics
import pandas as pd
from datetime import datetime
from optparse import OptionParser

directory = "./NIID-MNISTCIFARFMNIST-RANDOMLOW"
arquivos = glob(directory+"/*")

global_loss = {}
global_accuracy = {}

for arquivo in arquivos:
    if "initial" in arquivo:
        bs_id = arquivo.split("_")[-2]
        bs_dataset = arquivo.split("_")[-3]
        file_read = open(arquivo, "r")
        lines = file_read.readlines()

        if bs_id not in global_loss:
            global_loss[bs_id] = []
        if bs_id not in global_accuracy:
            global_accuracy[bs_id] = []

        for line in lines:
            line_split = line.split(":")
            if "," in line_split[3].replace("[","").replace("]","").replace("}\n",""):
                value_acc = float(line_split[3].replace("[","").replace("]","").replace("}\n","").split(",")[-1])
                value_loss = float(line_split[2].replace("[","").replace("]","").replace("}\n","").split(",")[-2])
                if "INITIALIZE_PARAMETERS" in line_split[0]:
                    global_accuracy[bs_id].append((value_acc, bs_dataset, "INITIALIZE"))
                    global_loss[bs_id].append((value_loss, bs_dataset, "INITIALIZE"))
            else:
                value_acc = float(line_split[3].replace("[","").replace("]","").replace("}\n",""))
                value_loss = float(line_split[2].replace("[","").replace("]","").replace(", 'accuracy'",""))
                if "INITIALIZE_PARAMETERS" in line_split[0]:
                    global_accuracy[bs_id].append((value_acc, bs_dataset, "INITIALIZE"))
                    global_loss[bs_id].append((value_loss, bs_dataset, "INITIALIZE"))
            break

    elif "global" in arquivo:
        bs_id = arquivo.split("_")[-2]
        bs_dataset = arquivo.split("_")[-3]
        file_read = open(arquivo, "r")
        lines = file_read.readlines()

        if bs_id not in global_loss:
            global_loss[bs_id] = []
        if bs_id not in global_accuracy:
            global_accuracy[bs_id] = []
            
        for line in lines:
            line_split = line.split(":")
            if "," in line_split[3].replace("[","").replace("]","").replace("}\n",""):
                value_acc = float(line_split[3].replace("[","").replace("]","").replace("}\n","").split(",")[-1])
                value_loss = float(line_split[2].replace("[","").replace("]","").replace("}\n","").split(",")[-2])
                if "FIT" in line_split[0]:
                    global_accuracy[bs_id].append((value_acc, bs_dataset, "FIT"))
                    global_loss[bs_id].append((value_loss, bs_dataset, "FIT"))
                elif "EVALUATE" in line_split[0]:
                    global_accuracy[bs_id].append((value_acc, bs_dataset, "EVALUATE"))
                    global_loss[bs_id].append((value_loss, bs_dataset, "EVALUATE"))
            else:
                value_acc = float(line_split[3].replace("[","").replace("]","").replace("}\n",""))
                value_loss = float(line_split[2].replace("[","").replace("]","").replace(", 'accuracy'",""))
                if "FIT" in line_split[0]:
                    global_accuracy[bs_id].append((value_acc, bs_dataset, "FIT"))
                    global_loss[bs_id].append((value_loss, bs_dataset, "FIT"))
                elif "EVALUATE" in line_split[0]:
                    global_accuracy[bs_id].append((value_acc, bs_dataset, "EVALUATE"))
                    global_loss[bs_id].append((value_loss, bs_dataset, "EVALUATE"))

loss_fit = []
loss_evaluate = []

acc_fit = []
acc_evaluate = []
#MNIST = 1
#FMNIST = 2
#CIFAR = 3
for chave in global_loss.keys():
    if int(chave) == 3: 
        for value in global_loss[chave]:
            if "INITIALIZE" ==  value[2]:
                loss_fit.insert(0, value[0])
                loss_evaluate.insert(0, value[0])
            elif "FIT" ==  value[2]:
                loss_fit.append(value[0])
            elif "EVALUATE" ==  value[2]:
                loss_evaluate.append(value[0])
    
for chave in global_accuracy.keys():
    if int(chave) == 3: 
        for value in global_accuracy[chave]: 
            if "INITIALIZE" ==  value[2]:
                acc_fit.insert(0, value[0])
                acc_evaluate.insert(0, value[0])
            elif "FIT" ==  value[2]:
                acc_fit.append(value[0])
            elif "EVALUATE" ==  value[2]:
                acc_evaluate.append(value[0])


communication_round = np.arange(len(acc_fit))
my_dpi=96
plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
plt.xticks(fontsize=18)
plt.yticks(fontsize=18)

plt.plot(communication_round, acc_fit, linewidth=1, linestyle="solid", marker=".", color="black")
plt.xlabel("Communication Round(#)", fontsize=18)
plt.ylabel("(Global) Train Accuracy", fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("Global_Train_ACC.png", format="png", dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("Global_Train_ACC.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
##################################################################################################################
communication_round = np.arange(len(acc_evaluate))
my_dpi=96
plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
plt.xticks(fontsize=18)
plt.yticks(fontsize=18)

plt.plot(communication_round, acc_evaluate, linewidth=1, linestyle="solid", marker=".", color="black")
plt.xlabel("Communication Round(#)", fontsize=18)
plt.ylabel("(Global) Test Accuracy", fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("Global_Test_ACC.png", format="png", dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("Global_Test_ACC.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
##################################################################################################################
communication_round = np.arange(len(loss_fit))
my_dpi=96
plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
plt.xticks(fontsize=18)
plt.yticks(fontsize=18)

plt.plot(communication_round, loss_fit, linewidth=1, linestyle="solid", marker=".", color="black")
plt.xlabel("Communication Round(#)", fontsize=18)
plt.ylabel("(Global) Train Loss", fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("Global_Train_LOSS.png", format="png", dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("Global_Train_LOSS.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
##################################################################################################################
communication_round = np.arange(len(loss_evaluate))
my_dpi=96
plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
plt.xticks(fontsize=18)
plt.yticks(fontsize=18)

plt.plot(communication_round, loss_evaluate, linewidth=1, linestyle="solid", marker=".", color="black")
plt.xlabel("Communication Round(#)", fontsize=18)
plt.ylabel("(Global) Test Loss", fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("Global_Test_LOSS.png", format="png", dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("Global_Test_LOSS.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)