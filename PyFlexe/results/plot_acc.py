from matplotlib import pyplot as plt
from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes, mark_inset
import numpy as np
from glob import glob
import statistics
import csv
import pandas as pd
from datetime import datetime

#plt.rcParams['hatch.linewidth'] = 0.5

dict_all = {}
dict_rsu_round = {}
dict_rsu_ids = {}
dict_rsu_wsm = {}

RESULT_SCENARIO = "01_SIGN_IID"

#RESULT_SCENARIO = "05_SIGN_IID"
#RESULT_SCENARIO = "05_SIGN_NONIID"

#RESULT_SCENARIO = "01_FMNIST_IID"

#RESULT_SCENARIO = "05_FMNIST_IID"
#RESULT_SCENARIO = "05_FMNIST_NONIID"
#RESULT_SCENARIO = "01_FMNIST_NONIID"

folders = glob("./*")
for folder in folders:
    if RESULT_SCENARIO in folder:
        files = glob(folder+"/omnetpp/*_vec_.csv")
        files_sca = glob(folder + "/omnetpp/*.sca")
        for archive in files_sca:
            with open(archive) as csv_file:
                file_read = open(archive, "r")
                chave = archive.split("/")[3].replace("-#0.sca", "").split("_")[0]
                print(chave)
                if chave not in dict_rsu_wsm:
                    dict_rsu_wsm[chave] = []
                lines = file_read.readlines()
                for line in lines:
                    line_split = line.split(" ")
                    if "generatedWSMs" in line:
                        dict_rsu_wsm[chave].append(float(line_split[3]))
        for archive in files:
            with open(archive) as csv_file:
               lines = csv.reader(csv_file, delimiter=',')
               for line in lines:
                   if "configname" in line[4]:
                       chave = line[5].split("_")[0]
                   if "rsu" in line[2]:
                       if "roundCount" in line[3] and "vector" in line[1]:
                           dict_rsu_round[chave] = line[6].split(" ")
                       elif "selectCount" in line[3] and "vector" in line[1]:
                           all_ids = line[7].split(" ")
                           all_times = line[6].split(" ")
                           all_ids_times = []
                           for veh_id, veh_time in zip(all_ids, all_times):
                               all_ids_times.append((int(veh_id), int(float(veh_time))))
                           dict_rsu_ids[chave] = all_ids_times
                           
        sub_folders = glob(folder+"/model_results/*")
        for sub_folder in sub_folders:
            files = glob(sub_folder+"/*")
            arch = sub_folder.split("/")
            chave = arch[3].replace("IID_", "").replace("_GRID_", "-").replace("_", "-")
            for archive in files:
                file_read = open(archive, "r")
                lines = file_read.readlines()
                arch = archive.split("/")
                key = arch[4].replace("model_","").replace(".txt","")
                if chave not in dict_all:
                    dict_all[chave] = {}
                dict_all[chave][key] = []
                for line in lines:
                    line_split = line.split(":")
                    if "," in line_split[3].replace("[","").replace("]","").replace("}\n",""):
                        value_acc = float(line_split[3].replace("[","").replace("]","").replace("}\n","").split(",")[-1])
                        value_loss = float(line_split[2].replace("[","").replace("]","").replace("}\n","").split(",")[-2])
                        if "FIT" in line_split[0]:
                            dict_all[chave][key].append((value_loss, value_acc, "FIT"))
                        elif "EVALUATE" in line_split[0]:
                            dict_all[chave][key].append((value_loss, value_acc, "EVALUATE"))
                        elif "INITIALIZE_PARAMETERS" in line_split[0]:
                            dict_all[chave][key].append((value_loss, value_acc, "INITIALIZE"))
                    else:
                        value_acc = float(line_split[3].replace("[","").replace("]","").replace("}\n",""))
                        value_loss = float(line_split[2].replace("[","").replace("]","").replace(", 'accuracy'",""))
                        if "FIT" in line_split[0]:
                            dict_all[chave][key].append((value_loss, value_acc, "FIT"))
                        elif "EVALUATE" in line_split[0]:
                            dict_all[chave][key].append((value_loss, value_acc, "EVALUATE"))
                        elif "INITIALIZE_PARAMETERS" in line_split[0]:
                            dict_all[chave][key].append((value_loss, value_acc, "INITIALIZE"))


   
proposals = sorted(dict_all.keys())
floe_acc = []
safa_acc = []
semi_acc = []
fedcs_acc = []

e_floe_acc = []
e_safa_acc = []
e_semi_acc = []
e_fedcs_acc = []

floe_loss = []
safa_loss = []
semi_loss = []
fedcs_loss = []

e_floe_loss = []
e_safa_loss = []
e_semi_loss = []
e_fedcs_loss = []
for key in proposals:
    for veh_id in dict_all[key]:
        if "global" in veh_id:
            loss = []
            acc = []
            for value in dict_all[key][veh_id]:
                if "FIT" in value[2]:
                    pass
                if "EVALUATE" in value[2]:
                    loss.append(value[0])
                    acc.append(value[1])
            if "FLOE" in key:
                floe_acc.append(np.mean(acc))
                e_floe_acc.append(statistics.stdev(acc))
                floe_loss.append(np.mean(loss))
                e_floe_loss.append(statistics.stdev(loss))
               
            if "SAFA" in key:
                safa_acc.append(np.mean(acc))
                e_safa_acc.append(statistics.stdev(acc))
                safa_loss.append(np.mean(loss))
                e_safa_loss.append(statistics.stdev(loss))
               
            if "SEMI" in key:
                semi_acc.append(np.mean(acc))
                e_semi_acc.append(statistics.stdev(acc))
                semi_loss.append(np.mean(loss))
                e_semi_loss.append(statistics.stdev(loss))

            if "FEDCS" in key:
                fedcs_acc.append(np.mean(acc))
                e_fedcs_acc.append(statistics.stdev(acc))
                fedcs_loss.append(np.mean(loss))
                e_fedcs_loss.append(statistics.stdev(loss))

data_acc = [floe_acc, safa_acc, semi_acc, fedcs_acc]
data_loss = [floe_loss, safa_loss, semi_loss, fedcs_loss]
#################################################################################################
X = np.arange(3)

my_dpi=96
plt.figure(figsize=(800/my_dpi, 650/my_dpi), dpi=my_dpi)
plt.xticks(fontsize=18)
plt.yticks(fontsize=18)


plt.bar(X - 0.1875, data_acc[2], yerr=e_semi_acc, color = '#C0C0C0', label="SEMI-SYNC", width = 0.125)
plt.bar(X - 0.0625, data_acc[3], yerr=e_fedcs_acc, color = '#A9A9A9', label="FedCS", width = 0.125)
plt.bar(X + 0.0625, data_acc[1], yerr=e_safa_acc, color = '#808080', label="SAFA", width = 0.125)
plt.bar(X + 0.1875, data_acc[0], yerr=e_floe_acc, color = '#696969', label="FLOE", width = 0.125)

plt.ylabel("Accuracy", fontsize=18)
plt.xticks(X, ['Low Density', 'Medium Density', 'High Density'])
plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("./"+RESULT_SCENARIO+"_acc_bar.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("./"+RESULT_SCENARIO+"_acc_bar.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
#################################################################################################
plt.clf()
plt.cla()
plt.close()

my_dpi=96
plt.figure(figsize=(800/my_dpi, 650/my_dpi), dpi=my_dpi)
plt.xticks(fontsize=18)
plt.yticks(fontsize=18)


plt.bar(X - 0.1875, data_loss[2], yerr=e_semi_loss, color = '#C0C0C0', label="SEMI-SYNC", width = 0.125)
plt.bar(X - 0.0625, data_loss[3], yerr=e_semi_loss, color = '#A9A9A9', label="FedCS", width = 0.125)
plt.bar(X + 0.0625, data_loss[1], yerr=e_safa_loss, color = '#808080', label="SAFA", width = 0.125)
plt.bar(X + 0.1875, data_loss[0], yerr=e_floe_loss, color = '#696969', label="FLOE", width = 0.125)

plt.ylabel("Loss", fontsize=18)
plt.xticks(X, ['Low Density', 'Medium Density', 'High Density'])
plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("./"+RESULT_SCENARIO+"_loss_bar.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("./"+RESULT_SCENARIO+"_loss_bar.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)


#################################################################################################
if RESULT_SCENARIO == "01_SIGN_IID":
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.94, 1)


    acc = []
    for value in dict_all["SIGN-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
                    
    acc.insert(0, dict_all["SIGN-SEMISYNC-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["SIGN-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SAFA-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    acc = []
    for value in dict_all["SIGN-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FLOE-HIGH"]["initial"][0][1])
    x_floe = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    x_floe.insert(0, 0.0)
    plt.plot(x_floe[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["SIGN-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FEDCS-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    x.insert(0, 0.0)

    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')


    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.94, 1)

    acc = []
    for value in dict_all["SIGN-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SEMISYNC-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["SIGN-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SAFA-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["SIGN-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FLOE-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["SIGN-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FEDCS-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.94, 1)

    acc = []
    for value in dict_all["SIGN-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SEMISYNC-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["SIGN-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SAFA-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["SIGN-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FLOE-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    acc = []
    for value in dict_all["SIGN-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FEDCS-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["SIGN-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
            
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["SIGN-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["SIGN-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["SIGN-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["SIGN-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["SIGN-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    loss = []
    for value in dict_all["SIGN-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    loss = []
    for value in dict_all["SIGN-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)

    loss = []
    for value in dict_all["SIGN-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["SIGN-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["SIGN-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["SIGN-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################

if RESULT_SCENARIO == "01_FMNIST_IID":
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)


    acc = []
    for value in dict_all["FMNIST-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
                    
    acc.insert(0, dict_all["FMNIST-SEMISYNC-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["FMNIST-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SAFA-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    acc = []
    for value in dict_all["FMNIST-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FLOE-HIGH"]["initial"][0][1])
    x_floe = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    x_floe.insert(0, 0.0)
    plt.plot(x_floe[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["FMNIST-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FEDCS-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    x.insert(0, 0.0)

    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')


    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)

    acc = []
    for value in dict_all["FMNIST-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SEMISYNC-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["FMNIST-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SAFA-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["FMNIST-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FLOE-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["FMNIST-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FEDCS-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)

    acc = []
    for value in dict_all["FMNIST-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SEMISYNC-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["FMNIST-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SAFA-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["FMNIST-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FLOE-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    acc = []
    for value in dict_all["FMNIST-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FEDCS-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["FMNIST-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
            
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["FMNIST-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["FMNIST-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["FMNIST-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["FMNIST-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["FMNIST-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    loss = []
    for value in dict_all["FMNIST-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    loss = []
    for value in dict_all["FMNIST-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)

    loss = []
    for value in dict_all["FMNIST-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["FMNIST-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["FMNIST-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["FMNIST-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################

if RESULT_SCENARIO == "05_FMNIST_IID":
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)


    acc = []
    for value in dict_all["FMNIST-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
                    
    acc.insert(0, dict_all["FMNIST-SEMISYNC-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["FMNIST-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SAFA-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    acc = []
    for value in dict_all["FMNIST-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FLOE-HIGH"]["initial"][0][1])
    x_floe = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    x_floe.insert(0, 0.0)
    plt.plot(x_floe[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["FMNIST-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FEDCS-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    x.insert(0, 0.0)

    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    ##plt.plot([0,160], [0.9534, 0.9534], color="#696969", linewidth=2, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')


    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)

    acc = []
    for value in dict_all["FMNIST-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SEMISYNC-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["FMNIST-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SAFA-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["FMNIST-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FLOE-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["FMNIST-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FEDCS-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [0.9534, 0.9534], color="#696969", linewidth=2, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)

    acc = []
    for value in dict_all["FMNIST-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SEMISYNC-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["FMNIST-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-SAFA-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["FMNIST-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FLOE-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    acc = []
    for value in dict_all["FMNIST-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["FMNIST-FEDCS-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [0.9534, 0.9534], color="#696969", linewidth=2, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["FMNIST-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
            
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["FMNIST-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["FMNIST-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["FMNIST-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["FMNIST-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["FMNIST-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    loss = []
    for value in dict_all["FMNIST-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    loss = []
    for value in dict_all["FMNIST-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)

    loss = []
    for value in dict_all["FMNIST-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["FMNIST-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["FMNIST-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["FMNIST-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################

if RESULT_SCENARIO == "05_SIGN_IID":
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.94, 1)


    acc = []
    for value in dict_all["SIGN-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
                    
    acc.insert(0, dict_all["SIGN-SEMISYNC-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["SIGN-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SAFA-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    acc = []
    for value in dict_all["SIGN-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FLOE-HIGH"]["initial"][0][1])
    x_floe = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    x_floe.insert(0, 0.0)
    plt.plot(x_floe[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["SIGN-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FEDCS-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    x.insert(0, 0.0)

    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [1, 1], color="#696969", linewidth=3, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')


    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.94, 1)

    acc = []
    for value in dict_all["SIGN-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SEMISYNC-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["SIGN-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SAFA-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["SIGN-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FLOE-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["SIGN-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FEDCS-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [1, 1], color="#696969", linewidth=3, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.94, 1)

    acc = []
    for value in dict_all["SIGN-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SEMISYNC-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["SIGN-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-SAFA-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["SIGN-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FLOE-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    acc = []
    for value in dict_all["SIGN-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["SIGN-FEDCS-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [1, 1], color="#696969", linewidth=3, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["SIGN-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
            
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["SIGN-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["SIGN-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["SIGN-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["SIGN-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["SIGN-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    loss = []
    for value in dict_all["SIGN-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    loss = []
    for value in dict_all["SIGN-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)

    loss = []
    for value in dict_all["SIGN-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["SIGN-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["SIGN-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["SIGN-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################

if RESULT_SCENARIO == "05_SIGN_NONIID":
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    #plt.ylim(0.94, 1)


    acc = []
    for value in dict_all["NONSIGN-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
                    
    acc.insert(0, dict_all["NONSIGN-SEMISYNC-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["NONSIGN-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-SAFA-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    acc = []
    for value in dict_all["NONSIGN-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-FLOE-HIGH"]["initial"][0][1])
    x_floe = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    x_floe.insert(0, 0.0)
    plt.plot(x_floe[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["NONSIGN-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-FEDCS-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    x.insert(0, 0.0)

    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [1, 1], color="#696969", linewidth=3, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')


    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    #plt.ylim(0.94, 1)

    acc = []
    for value in dict_all["NONSIGN-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-SEMISYNC-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["NONSIGN-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-SAFA-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["NONSIGN-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-FLOE-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["NONSIGN-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-FEDCS-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [1, 1], color="#696969", linewidth=3, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    #plt.ylim(0.94, 1)

    acc = []
    for value in dict_all["NONSIGN-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-SEMISYNC-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["NONSIGN-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-SAFA-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["NONSIGN-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-FLOE-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    acc = []
    for value in dict_all["NONSIGN-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONSIGN-FEDCS-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [1, 1], color="#696969", linewidth=3, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["NONSIGN-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
            
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["NONSIGN-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["NONSIGN-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["NONSIGN-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["NONSIGN-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["NONSIGN-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    loss = []
    for value in dict_all["NONSIGN-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    loss = []
    for value in dict_all["NONSIGN-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)

    loss = []
    for value in dict_all["NONSIGN-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["NONSIGN-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["NONSIGN-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["NONSIGN-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################

if RESULT_SCENARIO == "01_FMNIST_NONIID":
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)


    acc = []
    for value in dict_all["NONFMNIST-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
                    
    acc.insert(0, dict_all["NONFMNIST-SEMISYNC-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["NONFMNIST-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SAFA-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    acc = []
    for value in dict_all["NONFMNIST-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FLOE-HIGH"]["initial"][0][1])
    x_floe = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    x_floe.insert(0, 0.0)
    plt.plot(x_floe[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["NONFMNIST-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FEDCS-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    x.insert(0, 0.0)

    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    ##plt.plot([0,160], [0.9534, 0.9534], color="#696969", linewidth=2, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')


    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)

    acc = []
    for value in dict_all["NONFMNIST-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SEMISYNC-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["NONFMNIST-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SAFA-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["NONFMNIST-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FLOE-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["NONFMNIST-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FEDCS-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [0.9534, 0.9534], color="#696969", linewidth=2, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)

    acc = []
    for value in dict_all["NONFMNIST-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SEMISYNC-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["NONFMNIST-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SAFA-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["NONFMNIST-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FLOE-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    acc = []
    for value in dict_all["NONFMNIST-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FEDCS-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [0.9534, 0.9534], color="#696969", linewidth=2, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["NONFMNIST-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
            
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["NONFMNIST-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["NONFMNIST-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["NONFMNIST-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["NONFMNIST-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["NONFMNIST-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    loss = []
    for value in dict_all["NONFMNIST-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    loss = []
    for value in dict_all["NONFMNIST-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)

    loss = []
    for value in dict_all["NONFMNIST-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["NONFMNIST-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["NONFMNIST-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["NONFMNIST-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################

if RESULT_SCENARIO == "05_FMNIST_NONIID":
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)
    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)


    acc = []
    for value in dict_all["NONFMNIST-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
                    
    acc.insert(0, dict_all["NONFMNIST-SEMISYNC-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["NONFMNIST-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SAFA-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    acc = []
    for value in dict_all["NONFMNIST-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FLOE-HIGH"]["initial"][0][1])
    x_floe = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    x_floe.insert(0, 0.0)
    plt.plot(x_floe[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["NONFMNIST-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FEDCS-HIGH"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    x.insert(0, 0.0)

    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    ##plt.plot([0,160], [0.9534, 0.9534], color="#696969", linewidth=2, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')


    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)

    acc = []
    for value in dict_all["NONFMNIST-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SEMISYNC-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["NONFMNIST-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SAFA-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["NONFMNIST-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FLOE-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    acc = []
    for value in dict_all["NONFMNIST-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FEDCS-LOW"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [0.9534, 0.9534], color="#696969", linewidth=2, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Accuracy", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylim(0.8, 0.9)

    acc = []
    for value in dict_all["NONFMNIST-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SEMISYNC-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    acc = []
    for value in dict_all["NONFMNIST-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-SAFA-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    acc = []
    for value in dict_all["NONFMNIST-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FLOE-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    acc = []
    for value in dict_all["NONFMNIST-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            acc.append(value[1])
    acc.insert(0, dict_all["NONFMNIST-FEDCS-MEDIUM"]["initial"][0][1])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    x.insert(0, 0.0)
    plt.plot(x[:len(acc)], acc, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")
    #plt.plot([0,160], [0.9534, 0.9534], color="#696969", linewidth=2, linestyle="solid", label="Centralized")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])

    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_acc_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["NONFMNIST-SEMISYNC-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
            
    x = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["NONFMNIST-SAFA-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["NONFMNIST-FLOE-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["NONFMNIST-FEDCS-HIGH"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_HIGH_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)


    loss = []
    for value in dict_all["NONFMNIST-SEMISYNC-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["NONFMNIST-SAFA-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

    loss = []
    for value in dict_all["NONFMNIST-FLOE-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")

    loss = []
    for value in dict_all["NONFMNIST-FEDCS-LOW"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_LOW_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    plt.xlabel("Simulation Time", fontsize=18)
    plt.ylabel("Loss", fontsize=18)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)

    loss = []
    for value in dict_all["NONFMNIST-SEMISYNC-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")


    loss = []
    for value in dict_all["NONFMNIST-SAFA-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")


    loss = []
    for value in dict_all["NONFMNIST-FLOE-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


    loss = []
    for value in dict_all["NONFMNIST-FEDCS-MEDIUM"]["global"]:
        if "FIT" in value[2]:
            pass
        if "EVALUATE" in value[2]:
            loss.append(value[0])
    x = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
    plt.plot(x[:len(loss)], loss, color="#A9A9A9", linewidth=2, linestyle="dashdot", label="FedCS", marker="x")

    new_x=[0, 40, 80, 120, 160]
    plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_loss_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
    #################################################################################################

plt.clf()
plt.cla()
plt.close()
floe_rounds = []
safa_rounds = []
semi_rounds = []
fedcs_rounds = []

my_dpi=96
plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

rounds_semi_high = [float(value) for value in dict_rsu_round["SemiSync-HIGH"]]
rounds_semi_high.insert(0, 0.0)

rounds_safa_high = [float(value) for value in dict_rsu_round["SAFA-HIGH"]]
rounds_safa_high.insert(0, 0.0)

rounds_floe_high = [float(value) for value in dict_rsu_round["FLOE-HIGH"]]
rounds_floe_high.insert(0, 0.0)

rounds_fedcs_high = [float(value) for value in dict_rsu_round["FedCS-HIGH"]]
rounds_fedcs_high.insert(0, 0.0)


rounds_semi_medium = [float(value) for value in dict_rsu_round["SemiSync-MEDIUM"]]
rounds_semi_medium.insert(0, 0.0)

rounds_safa_medium = [float(value) for value in dict_rsu_round["SAFA-MEDIUM"]]
rounds_safa_medium.insert(0, 0.0)

rounds_floe_medium = [float(value) for value in dict_rsu_round["FLOE-MEDIUM"]]
rounds_floe_medium.insert(0, 0.0)

rounds_fedcs_medium = [float(value) for value in dict_rsu_round["FedCS-MEDIUM"]]
rounds_fedcs_medium.insert(0, 0.0)


rounds_semi_low = [float(value) for value in dict_rsu_round["SemiSync-LOW"]]
rounds_semi_low.insert(0, 0.0)

rounds_safa_low = [float(value) for value in dict_rsu_round["SAFA-LOW"]]
rounds_safa_low.insert(0, 0.0)

rounds_floe_low = [float(value) for value in dict_rsu_round["FLOE-LOW"]]
rounds_floe_low.insert(0, 0.0)

rounds_fedcs_low = [float(value) for value in dict_rsu_round["FedCS-LOW"]]
rounds_fedcs_low.insert(0, 0.0)

semi_rounds.append(len(rounds_semi_low))
semi_rounds.append(len(rounds_semi_medium))
semi_rounds.append(len(rounds_semi_high))

safa_rounds.append(len(rounds_safa_low))
safa_rounds.append(len(rounds_safa_medium))
safa_rounds.append(len(rounds_safa_high))

floe_rounds.append(len(rounds_floe_low))
floe_rounds.append(len(rounds_floe_medium))
floe_rounds.append(len(rounds_floe_high))

fedcs_rounds.append(len(rounds_fedcs_low))
fedcs_rounds.append(len(rounds_fedcs_medium))
fedcs_rounds.append(len(rounds_fedcs_high))

data_round = [floe_rounds, safa_rounds, semi_rounds, fedcs_rounds]
X = np.arange(3)

my_dpi=96
plt.figure(figsize=(800/my_dpi, 650/my_dpi), dpi=my_dpi)
plt.xticks(fontsize=18)
plt.yticks(fontsize=18)


plt.bar(X - 0.1875, data_round[2], yerr=e_semi_acc, color = '#C0C0C0', label="SEMI-SYNC", width = 0.125)
plt.bar(X - 0.0625, data_round[3], yerr=e_fedcs_acc, color = '#A9A9A9', label="FedCS", width = 0.125)
plt.bar(X + 0.0625, data_round[1], yerr=e_safa_acc, color = '#808080', label="SAFA", width = 0.125)
plt.bar(X + 0.1875, data_round[0], yerr=e_floe_acc, color = '#696969', label="FLOE", width = 0.125)

plt.ylabel("# of Communication Round", fontsize=18)
plt.xticks(X, ['Low Density', 'Medium Density', 'High Density'])
plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("./"+RESULT_SCENARIO+"_rounds_bar.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("./"+RESULT_SCENARIO+"_rounds_bar.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
#################################################################################################
plt.clf()
plt.cla()
plt.close()

my_dpi=96
plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

floe_ids = [len(dict_rsu_ids["FLOE-LOW"]), len(dict_rsu_ids["FLOE-MEDIUM"]), len(dict_rsu_ids["FLOE-HIGH"])]
safa_ids = [len(dict_rsu_ids["SAFA-LOW"]), len(dict_rsu_ids["SAFA-MEDIUM"]), len(dict_rsu_ids["SAFA-HIGH"])]
semi_ids = [len(dict_rsu_ids["SemiSync-LOW"]), len(dict_rsu_ids["SemiSync-MEDIUM"]), len(dict_rsu_ids["SemiSync-HIGH"])]
fedcs_ids = [len(dict_rsu_ids["FedCS-LOW"]), len(dict_rsu_ids["FedCS-MEDIUM"]), len(dict_rsu_ids["FedCS-HIGH"])]

data_ids = [floe_ids, safa_ids, semi_ids, fedcs_ids]
X = np.arange(3)

plt.bar(X - 0.1875, data_ids[2], yerr=e_semi_acc, color = '#C0C0C0', label="SEMI-SYNC", width = 0.125)
plt.bar(X - 0.0625, data_ids[3], yerr=e_fedcs_acc, color = '#A9A9A9', label="FedCS", width = 0.125)
plt.bar(X + 0.0625, data_ids[1], yerr=e_safa_acc, color = '#808080', label="SAFA", width = 0.125)
plt.bar(X + 0.1875, data_ids[0], yerr=e_floe_acc, color = '#696969', label="FLOE", width = 0.125)

plt.ylabel("# of Selected Clients", fontsize=18)
plt.xticks(X, ['Low Density', 'Medium Density', 'High Density'])
plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("./"+RESULT_SCENARIO+"_ids_bar.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("./"+RESULT_SCENARIO+"_ids_bar.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
#################################################################################################
plt.clf()
plt.cla()
plt.close()

my_dpi=96
plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

plt.xlabel("Simulation Time", fontsize=18)
plt.ylabel("# of Selected Clients", fontsize=18)

plt.xticks(fontsize=18)
plt.yticks(fontsize=18)

floe_sel = []
safa_sel = []
fedcs_sel = []
semi_sel = []

x = []
cdf_dict = {}
for selected in dict_rsu_ids["SemiSync-LOW"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
for chave in cdf_dict.keys():
    semi_sel.append(len(cdf_dict[chave]))
    x.append(chave)

semi_sel = np.array(semi_sel).cumsum() 
plt.plot(x, semi_sel, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")

x = []
cdf_dict = {}
for selected in dict_rsu_ids["SAFA-LOW"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
for chave in cdf_dict.keys():
    safa_sel.append(len(cdf_dict[chave]))
    x.append(chave)

safa_sel = np.array(safa_sel).cumsum() 
plt.plot(x, safa_sel, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

x = []
cdf_dict = {}
for selected in dict_rsu_ids["FLOE-LOW"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
        
for chave in cdf_dict.keys():
    floe_sel.append(len(cdf_dict[chave]))
    x.append(chave)

floe_sel = np.array(floe_sel).cumsum() 
plt.plot(x, floe_sel, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


x = []    
cdf_dict = {}
for selected in dict_rsu_ids["FedCS-LOW"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
for chave in cdf_dict.keys():
    fedcs_sel.append(len(cdf_dict[chave]))
    x.append(chave)

fedcs_sel = np.array(fedcs_sel).cumsum() 
plt.plot(x, fedcs_sel, color="#A9A9A9", linewidth=2,linestyle="dashdot", label="FedCS", marker="x")


new_x=[0, 40, 80, 120, 160]
plt.xticks(new_x, labels=["11:15", "11:30", "11:45", "12:00", "12:15"])
plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("./"+RESULT_SCENARIO+"_LOW_cumsum_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("./"+RESULT_SCENARIO+"_LOW_cumsum_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
#################################################################################################


plt.clf()
plt.cla()
plt.close()

my_dpi=96
plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

plt.xlabel("Simulation Time", fontsize=18)
plt.ylabel("# of Selected Clients", fontsize=18)

plt.xticks(fontsize=18)
plt.yticks(fontsize=18)

floe_sel = []
safa_sel = []
fedcs_sel = []
semi_sel = []

x = []
cdf_dict = {}
for selected in dict_rsu_ids["SemiSync-MEDIUM"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
for chave in cdf_dict.keys():
    semi_sel.append(len(cdf_dict[chave]))
    x.append(chave)

semi_sel = np.array(semi_sel).cumsum() 
plt.plot(x, semi_sel, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")

x = []
cdf_dict = {}
for selected in dict_rsu_ids["SAFA-MEDIUM"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
for chave in cdf_dict.keys():
    safa_sel.append(len(cdf_dict[chave]))
    x.append(chave)

safa_sel = np.array(safa_sel).cumsum() 
plt.plot(x, safa_sel, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

x = []
cdf_dict = {}
for selected in dict_rsu_ids["FLOE-MEDIUM"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
        
for chave in cdf_dict.keys():
    floe_sel.append(len(cdf_dict[chave]))
    x.append(chave)

floe_sel = np.array(floe_sel).cumsum() 
plt.plot(x, floe_sel, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


x = []    
cdf_dict = {}
for selected in dict_rsu_ids["FedCS-MEDIUM"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
for chave in cdf_dict.keys():
    fedcs_sel.append(len(cdf_dict[chave]))
    x.append(chave)

fedcs_sel = np.array(fedcs_sel).cumsum() 
plt.plot(x, fedcs_sel, color="#A9A9A9", linewidth=2,linestyle="dashdot", label="FedCS", marker="x")


new_x=[0, 40, 80, 120, 160]
plt.xticks(new_x, labels=["13:00", "13:15", "13:30", "13:45", "14:00"])
plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_cumsum_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("./"+RESULT_SCENARIO+"_MEDIUM_cumsum_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
#################################################################################################
plt.clf()
plt.cla()
plt.close()

my_dpi=96
plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

plt.xlabel("Simulation Time", fontsize=18)
plt.ylabel("# of Selected Clients", fontsize=18)

plt.xticks(fontsize=18)
plt.yticks(fontsize=18)

floe_sel = []
safa_sel = []
fedcs_sel = []
semi_sel = []

x = []
cdf_dict = {}
for selected in dict_rsu_ids["SemiSync-HIGH"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
for chave in cdf_dict.keys():
    semi_sel.append(len(cdf_dict[chave]))
    x.append(chave)

semi_sel = np.array(semi_sel).cumsum() 
plt.plot(x, semi_sel, color="#C0C0C0", linewidth=2, linestyle="dotted", label='SEMI-SYNC', marker=".")

x = []
cdf_dict = {}
for selected in dict_rsu_ids["SAFA-HIGH"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
for chave in cdf_dict.keys():
    safa_sel.append(len(cdf_dict[chave]))
    x.append(chave)

safa_sel = np.array(safa_sel).cumsum() 
plt.plot(x, safa_sel, color="#808080", linewidth=2, linestyle="dashed", label='SAFA', marker="p")

x = []
cdf_dict = {}
for selected in dict_rsu_ids["FLOE-HIGH"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
        
for chave in cdf_dict.keys():
    floe_sel.append(len(cdf_dict[chave]))
    x.append(chave)

floe_sel = np.array(floe_sel).cumsum() 
plt.plot(x, floe_sel, color="#696969", linewidth=2, linestyle="solid", label="FLOE", marker="d")


x = []    
cdf_dict = {}
for selected in dict_rsu_ids["FedCS-HIGH"]:
    if selected[1] not in cdf_dict.keys():
        cdf_dict[selected[1]] = []
        cdf_dict[selected[1]].append(selected[0])
    else:
        cdf_dict[selected[1]].append(selected[0])
for chave in cdf_dict.keys():
    fedcs_sel.append(len(cdf_dict[chave]))
    x.append(chave)

fedcs_sel = np.array(fedcs_sel).cumsum() 
plt.plot(x, fedcs_sel, color="#A9A9A9", linewidth=2,linestyle="dashdot", label="FedCS", marker="x")


new_x=[0, 40, 80, 120, 160]
plt.xticks(new_x, labels=["08:00", "08:15", "08:30", "08:45", "09:00"])
plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
plt.grid(linestyle=':', linewidth='0.5')

plt.savefig("./"+RESULT_SCENARIO+"_HIGH_cumsum_line.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
plt.savefig("./"+RESULT_SCENARIO+"_HIGH_cumsum_line.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
"""



if  "SIGN" in RESULT_SCENARIO:
    model_size = 3.0
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    floe_ids = [np.mean(dict_rsu_wsm["FLOE-LOW"])*model_size, 	 np.mean(dict_rsu_wsm["FLOE-MEDIUM"])*model_size, 	 np.mean(dict_rsu_wsm["FLOE-HIGH"])*model_size]
    safa_ids = [np.mean(dict_rsu_wsm["SAFA-LOW"])*model_size, 	 np.mean(dict_rsu_wsm["SAFA-MEDIUM"])*model_size, 	 np.mean(dict_rsu_wsm["SAFA-HIGH"])*model_size]
    semi_ids = [np.mean(dict_rsu_wsm["SemiSync-LOW"])*model_size, 	 np.mean(dict_rsu_wsm["SemiSync-MEDIUM"])*model_size, 	 np.mean(dict_rsu_wsm["SemiSync-HIGH"])*model_size]
    fedcs_ids = [np.mean(dict_rsu_wsm["FedCS-LOW"])*model_size, 	 np.mean(dict_rsu_wsm["FedCS-MEDIUM"])*model_size, 	 np.mean(dict_rsu_wsm["FedCS-HIGH"])*model_size]


    data_ids = [floe_ids, safa_ids, semi_ids, fedcs_ids]
    X = np.arange(3)

    plt.bar(X - 0.1875, data_ids[3], yerr=e_fedcs_acc, color = '#A9A9A9', label="FedCS", width = 0.125)
    plt.bar(X - 0.0625, data_ids[2], yerr=e_semi_acc, color = '#C0C0C0', label="SEMI-SYNC", width = 0.125)
    plt.bar(X + 0.0625, data_ids[1], yerr=e_safa_acc, color = '#808080', label="SAFA", width = 0.125)
    plt.bar(X + 0.1875, data_ids[0], yerr=e_floe_acc, color = '#696969', label="FLOE", width = 0.125)

    plt.ylabel("Communication (MB)", fontsize=18)
    plt.xticks(X, ['Low Density', 'Medium Density', 'High Density'])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_wms_bar.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_wms_bar.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
if  "FMNIST" in RESULT_SCENARIO:
    model_size = 1.2
    plt.clf()
    plt.cla()
    plt.close()

    my_dpi=96
    plt.figure(figsize=(800/my_dpi, 600/my_dpi), dpi=my_dpi)

    floe_ids = [np.mean(dict_rsu_wsm["FLOE-MEDIUM"])*model_size, 	 np.mean(dict_rsu_wsm["FLOE-MEDIUM"])*model_size, 	 np.mean(dict_rsu_wsm["FLOE-HIGH"])*model_size]
    safa_ids = [np.mean(dict_rsu_wsm["SAFA-LOW"])*model_size, 	 np.mean(dict_rsu_wsm["SAFA-MEDIUM"])*model_size, 	 np.mean(dict_rsu_wsm["SAFA-HIGH"])*model_size]
    semi_ids = [np.mean(dict_rsu_wsm["SemiSync-LOW"])*model_size, 	 np.mean(dict_rsu_wsm["SemiSync-MEDIUM"])*model_size, 	 np.mean(dict_rsu_wsm["SemiSync-HIGH"])*model_size]
    fedcs_ids = [np.mean(dict_rsu_wsm["FedCS-LOW"])*model_size, 	 np.mean(dict_rsu_wsm["FedCS-MEDIUM"])*model_size, 	 np.mean(dict_rsu_wsm["FedCS-HIGH"])*model_size]

    data_ids = [floe_ids, safa_ids, semi_ids, fedcs_ids]
    X = np.arange(3)

    plt.bar(X - 0.1875, data_ids[2], yerr=e_semi_acc, color = '#C0C0C0', label="SEMI-SYNC", width = 0.125)
    plt.bar(X - 0.0625, data_ids[3], yerr=e_fedcs_acc, color = '#A9A9A9', label="FedCS", width = 0.125)
    plt.bar(X + 0.0625, data_ids[1], yerr=e_safa_acc, color = '#808080', label="SAFA", width = 0.125)
    plt.bar(X + 0.1875, data_ids[0], yerr=e_floe_acc, color = '#696969', label="FLOE", width = 0.125)

    plt.ylabel("Communication (MB)", fontsize=18)
    plt.xticks(X, ['Low Density', 'Medium Density', 'High Density'])
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2), fancybox=False, shadow=False, ncol=2, fontsize=18)
    plt.grid(linestyle=':', linewidth='0.5')

    plt.savefig("./"+RESULT_SCENARIO+"_wms_bar.eps", format="eps", transparent=True, dpi=200, bbox_inches='tight', pad_inches=0.05)
    plt.savefig("./"+RESULT_SCENARIO+"_wms_bar.png", format='png', dpi=200, bbox_inches='tight', pad_inches=0.05)
"""
