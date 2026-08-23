import pandas as pd
import os
from sklearn.metrics import confusion_matrix

from core.application.GenericApp import GenericApp
from core.model.model_definition_tf import ModelCreation
from core.dataset.dataset_utils_tf import ManageDatasets

class ColisaoApp(GenericApp):
    def __init__(self):
        super().__init__()
        # 1. Define o nome do dataset que criamos no dataset_utils_tf.py
        self.dataset_name = 'ColisaoFederada' 
        
        self.resultados = []
        self.step = 0
        print("ColisaoApp inicializado")

        
    def get_model(self, input_shape, num_classes):
        # 2. Chama especificamente o seu novo modelo MLP
        return ModelCreation().create_MLP_Colisao(input_shape, num_classes)

    def load_dataset(self, n_clients, non_iid):
        # 3. Carrega os dados usando a lógica de SMOTE e Sequências
        return ManageDatasets(self.cid).select_dataset(self.dataset_name, n_clients, non_iid)
        
        
    def registrar_resultado(self, status_real, status_previsto):
        self.step += 1
        self.resultados.append({
            "step": self.step,
            "status_real": int(status_real),
            "status_previsto": int(status_previsto)
        })

       # salva periodicamente
        if self.step % 50 == 0:  # a cada 50 amostras (ajuste se quiser)
            self.salvar_matriz_confusao_parcial()


    def salvar_matriz_confusao_parcial(self):
        if len(self.resultados) == 0:
            return

        df = pd.DataFrame(self.resultados)

        y_true = df["status_real"]
        y_pred = df["status_previsto"]

        cm = confusion_matrix(y_true, y_pred)

        output_dir = "/home/flexe/PyFlexe/results"
        os.makedirs(output_dir, exist_ok=True)

        output_file = os.path.join(
            output_dir,
            f"matriz_confusao_parcial_cliente_{self.cid}.txt"
        )

        with open(output_file, "w") as f:
            f.write(f"MATRIZ DE CONFUSÃO PARCIAL — step {self.step}\n")
            f.write("=" * 50 + "\n\n")
            f.write(str(cm))

        print(f"💾 Matriz parcial salva (step {self.step})")




        
    def salvar_excel(self):
        print(">>> salvar_excel() foi chamado <<<")
        if len(self.resultados) == 0:
            return

        df = pd.DataFrame(self.resultados)

        output_dir = "/home/flexe/PyFlexe/results"
        os.makedirs(output_dir, exist_ok=True)

        file_path = os.path.join(
            output_dir,
            "ColisaoFederada_resultados.xlsx"
        )

        df.to_excel(file_path, index=False)

        print(f"Excel salvo em: {file_path}")

    def avaliar(self):
        if len(self.resultados) == 0:
            print("⚠️ Nenhum resultado para avaliar")
            return

        df = pd.DataFrame(self.resultados)

        y_true = df["status_real"]
        y_pred = df["status_previsto"]

        cm = confusion_matrix(y_true, y_pred)

        print("\n🧩 MATRIZ DE CONFUSÃO 🧩")
        print(cm)

        # Salvar em TXT
        output_dir = "/home/flexe/PyFlexe/results"
        os.makedirs(output_dir, exist_ok=True)

        output_file = os.path.join(
            output_dir,
            f"matriz_confusao_cliente_{self.cid}.txt"
        )

        with open(output_file, "w") as f:
            f.write("MATRIZ DE CONFUSÃO - CONJUNTO DE TESTE\n")
            f.write("=" * 40 + "\n\n")
            f.write(str(cm))

        print(f"✅ Matriz de confusão salva em: {output_file}")

        return cm

    def finalizar(self):
        print("🔚 Finalizando ColisaoApp")
        self.avaliar()
        self.salvar_excel()





