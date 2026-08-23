"""
O código replica o dataset em outros veículos, sem precisar repetir o processo.
"""
from glob import glob
import random
import shutil

num_all_veh = 31500
arquivos = glob("*.pickle")
dict_veh = {}
list_veh = []
for arquivo in arquivos:
    id_veh = arquivo.replace(".pickle", "").split("_")[2]
    if int(id_veh) not in list_veh:
        list_veh.append(int(id_veh))

list_veh = sorted(list_veh)
start = list_veh[-1]+1

tamanho = len(list_veh)
contador = 0
for id_veh in range(start, num_all_veh+1):
    if contador >= tamanho:
        random.shuffle(list_veh)
        contador = 0
    novo_arquivo_train = "idx_train_"+str(id_veh)+".pickle"
    novo_arquivo_test = "idx_test_"+str(id_veh)+".pickle"
    old_arquivo_train = "idx_train_"+str(list_veh[contador])+".pickle"
    old_arquivo_test = "idx_test_"+str(list_veh[contador])+".pickle"
    print(novo_arquivo_train)
    print(novo_arquivo_test)
    print(old_arquivo_train)
    print(old_arquivo_test)
    shutil.copyfile(old_arquivo_train, novo_arquivo_train)
    shutil.copyfile(old_arquivo_test, novo_arquivo_test)
    contador = contador + 1
