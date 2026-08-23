import tensorflow as tf
from tensorflow.keras.models import Sequential, Model
from tensorflow.keras import layers, models
from tensorflow.keras.layers import Input, Conv1D, Conv2D, MaxPooling1D, Flatten, MaxPool2D, Dense, InputLayer, BatchNormalization, Dropout, MaxPooling2D, concatenate
from tensorflow.keras import initializers
from keras.optimizers import Adam
import os
import numpy as np
import os
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix, roc_curve, auc, matthews_corrcoef
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.metrics import matthews_corrcoef

import logging
logging.getLogger("tensorflow").setLevel(logging.ERROR)

tf.random.set_seed(42)
###########################################################################
# Limit GPU Memory Growth
gpus = tf.config.experimental.list_physical_devices('GPU')
if gpus:
	try:
		for gpu in gpus:
			tf.config.experimental.set_memory_growth(gpu, True)
	except RuntimeError as e:
		print(e)
###########################################################################
class ModelCreation():

	"""
	create_CNN 

	:param input_shape: Quantidade de amostras para treino
	:param num_classes: Quantidade de amostras para teste
	"""
	
	"""
    create_MLP_Colisao
    Modelo MLP otimizado para classificação de risco de colisão.
    Configurado para dados sequenciais (TIMESTEPS, FEATURES).
    """
    
	def create_MLP_COLISAO(self, input_shape, num_classes):
		"""
        Modelo MLP otimizado para classificação de risco de colisão.
        """
		model = Sequential([
            InputLayer(input_shape=(input_shape[1:])),
            Flatten(),
            Dense(32, activation='relu', 
                  kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42)),
            Dropout(0.3),
            Dense(num_classes, activation='softmax')
        ])

		model.compile(
            optimizer=tf.keras.optimizers.Adam(learning_rate=1e-3),
            loss='sparse_categorical_crossentropy',
            metrics=['accuracy']
        )
		print(f"✅ Modelo MLP Colisão criado com entrada {input_shape[1:]}")
		return model

    # --- NOVOS MÉTODOS PARA MÉTRICAS E AVALIAÇÃO ---

	def create_LSTM_COLISAO(self, input_shape, num_classes):

		model = Sequential([
			InputLayer(input_shape=(input_shape[1:])),

			layers.LSTM(64, return_sequences=False),
			Dropout(0.3),

			Dense(32, activation='relu',
				kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42)),

			Dense(num_classes, activation='softmax')
		])

		model.compile(
			optimizer=tf.keras.optimizers.Adam(learning_rate=1e-3),
			loss='sparse_categorical_crossentropy',
			metrics=['accuracy']
		)

		print(f"✅ Modelo LSTM Colisão criado com entrada {input_shape[1:]}")
		
		return model  

	def calcular_metricas_detalhadas(self, y_true, y_pred, y_prob, n_linhas, pasta_dest):
		"""
        Calcula Sensibilidade, Especificidade, F1, MCC, VP, VN, FP, FN e Curva ROC.
        Focado na Classe 2 (Colisão) como alvo positivo.
        """
		os.makedirs(pasta_dest, exist_ok=True)
        
        # Matriz de Confusão (0: Normal, 1: Risco, 2: Colisão)
		cm = confusion_matrix(y_true, y_pred, labels=[0, 1, 2])
        
        # Cálculo One-vs-Rest para a Classe 2 (Colisão)
		idx = 2
		tp = cm[idx, idx]
		fn = np.sum(cm[idx, :]) - tp
		fp = np.sum(cm[:, idx]) - tp
		tn = np.sum(cm) - (tp + fp + fn)

        # Métricas Protegidas contra divisão por zero
		sensibilidade = tp / (tp + fn) if (tp + fn) > 0 else 0
		especificidade = tn / (tn + fp) if (tn + fp) > 0 else 0
		precisao = tp / (tp + fp) if (tp + fp) > 0 else 0
		f1 = 2 * (precisao * sensibilidade) / (precisao + sensibilidade) if (precisao + sensibilidade) > 0 else 0
		mcc = matthews_corrcoef(y_true, y_pred)

        # Salvar em arquivo texto
		caminho_txt = os.path.join(pasta_dest, f"metricas_N{n_linhas}.txt")
		with open(caminho_txt, "w") as f:
			f.write(f"Resultados para {n_linhas} linhas a frente\n")
			f.write("-" * 30 + "\n")
			f.write(f"VP: {tp} | VN: {tn} | FP: {fp} | FN: {fn}\n")
			f.write(f"Sensibilidade (Recall): {sensibilidade:.4f}\n")
			f.write(f"Especificidade: {especificidade:.4f}\n")
			f.write(f"Precisao: {precisao:.4f}\n")
			f.write(f"F1-Score: {f1:.4f}\n")
			f.write(f"MCC: {mcc:.4f}\n")

        # Gerar e Salvar Curva ROC
		self._salvar_curva_roc(y_true, y_prob, n_linhas, pasta_dest)
        
		print(f"📊 Métricas para N={n_linhas} salvas em: {pasta_dest}")
		return mcc

	def _salvar_curva_roc(self, y_true, y_prob, n_linhas, pasta_dest):
		plt.figure(figsize=(8, 6))
		for i in range(y_prob.shape[1]): # Para cada classe (0, 1, 2)
			fpr, tpr, _ = roc_curve((y_true == i).astype(int), y_prob[:, i])
			roc_auc = auc(fpr, tpr)
			plt.plot(fpr, tpr, label=f'Classe {i} (AUC = {roc_auc:.2f})')
        
		plt.plot([0, 1], [0, 1], 'k--')
		plt.xlabel('Taxa de Falsos Positivos')
		plt.ylabel('Taxa de Verdadeiros Positivos')
		plt.title(f'Curva ROC - Predição {n_linhas} passos à frente')
		plt.legend(loc='lower right')
		plt.savefig(os.path.join(pasta_dest, f"roc_N{n_linhas}.png"))
		plt.close()
		
		
		
		
		
	def create_CNN_SIGN(self, input_shape, num_classes):
		model = Sequential()
		model.add(Conv2D(filters=32, kernel_size=(5,5), activation='relu', input_shape=input_shape[1:]))
		model.add(Conv2D(filters=32, kernel_size=(5,5), activation='relu'))
		model.add(MaxPool2D(pool_size=(2, 2)))
		model.add(Dropout(rate=0.25))
		model.add(Conv2D(filters=64, kernel_size=(3, 3), activation='relu'))
		model.add(Conv2D(filters=64, kernel_size=(3, 3), activation='relu'))
		model.add(MaxPool2D(pool_size=(2, 2)))
		model.add(Dropout(rate=0.25))
		model.add(Flatten())
		model.add(Dense(256, activation='relu'))
		model.add(Dropout(rate=0.5))
		model.add(Dense(num_classes, activation='softmax'))

		# Compilation of the model
		model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=1e-5), loss='categorical_crossentropy', metrics=['accuracy'])
		return model

	"""
	create_DNN 

	:param input_shape: Quantidade de amostras para treino
	:param num_classes: Quantidade de amostras para teste
	"""
	def create_DNN(self, input_shape, num_classes):
		input = Input(shape=(input_shape[1:]))
		x = Flatten()(input)
		x = Dense(512, activation='relu', kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42), bias_initializer=initializers.Zeros())(x)
		x = Dense(256, activation='relu', kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42), bias_initializer=initializers.Zeros())(x)
		x = Dense(32,  activation='relu', kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42), bias_initializer=initializers.Zeros())(x)
		out = Dense(num_classes, activation='softmax')(x)
		model = Model(inputs=input, outputs=[out])
		model.compile(optimizer=tf.keras.optimizers.SGD(learning_rate=1e-5), loss='sparse_categorical_crossentropy', metrics=['accuracy'])
		return model

	"""
	create_generic_model 

	:param input_shape: Quantidade de amostras para treino
	:param num_classes: Quantidade de amostras para teste
	"""
	def create_generic_model(self, input_shape, num_classes):
		# CREATE GENERIC MODEL
		model = tf.keras.models.Sequential([
			tf.keras.layers.Flatten(input_shape=(input_shape[1:])),
			tf.keras.layers.Dense(128, activation="relu", kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42), bias_initializer=initializers.Zeros()),
			tf.keras.layers.Dropout(0.2),
			tf.keras.layers.Dense(num_classes, activation="softmax", kernel_initializer=initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42), bias_initializer=initializers.Zeros()),
		])
		model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=1e-5), loss="sparse_categorical_crossentropy", metrics=["accuracy"])
		# CREATE GENERIC MODEL

		return model

	def create_CNN(self, input_shape, num_classes):
		model = models.Sequential([
			layers.Conv2D(32, (3, 3), activation='relu', input_shape=(input_shape[1], input_shape[2], 1)),
			layers.MaxPooling2D((2, 2)),
			layers.Conv2D(64, (3, 3), activation='relu'),
			layers.MaxPooling2D((2, 2)),
			layers.Conv2D(128, (3, 3), activation='relu'),
			layers.Flatten(),
			layers.Dense(128, activation='relu'),
			layers.Dense(num_classes, activation='softmax')
		])
		model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=1e-5), loss='sparse_categorical_crossentropy', metrics=['accuracy'])

		return model

	def create_VGG(self, input_shape, num_classes):
		model = models.Sequential([
			layers.Conv2D(64, (3, 3), activation='relu', padding='same', input_shape=(input_shape[1:])),
			layers.Conv2D(64, (3, 3), activation='relu', padding='same'),
			layers.MaxPooling2D((2, 2)),
			layers.Conv2D(128, (3, 3), activation='relu', padding='same'),
			layers.Conv2D(128, (3, 3), activation='relu', padding='same'),
			layers.MaxPooling2D((2, 2)),
			layers.Conv2D(256, (3, 3), activation='relu', padding='same'),
			layers.Conv2D(256, (3, 3), activation='relu', padding='same'),
			layers.MaxPooling2D((2, 2)),
			layers.Flatten(),
			layers.Dense(512, activation='relu'),
			layers.Dense(512, activation='relu'),
			layers.Dense(num_classes, activation='softmax')
		])

		model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=1e-5), loss='sparse_categorical_crossentropy', metrics=['accuracy'])
		return model

	"""
	create_LogisticRegression 

	:param input_shape: Quantidade de amostras para treino
	:param num_classes: Quantidade de amostras para teste
	"""
	def create_LogisticRegression(self, input_shape, num_classes):
		if len(input_shape) == 3:
			input = Input(shape=(input_shape[1], input_shape[2], 1))
		else:
			input = Input(shape=(input_shape[1:]))

		x = Flatten()(input)
		out = Dense(num_classes, activation='sigmoid')(x)

		model = Model(inputs=input, outputs=[out])
		model.compile(optimizer=tf.keras.optimizers.SGD(learning_rate=1e-5), loss='sparse_categorical_crossentropy', metrics=['accuracy'])
		return model
		
		
	def create_MobileNet(self, input_shape, num_classes):
		model = tf.keras.applications.MobileNet((32, 32, 3), classes=num_classes, weights=None)
		model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=1e-5), loss="sparse_categorical_crossentropy", metrics=["accuracy"])
		return model
		

	def create_ResNet(self, input_shape, num_classes):
		model = tf.keras.applications.ResNet50((32, 32, 3), classes=num_classes, weights=None)
		model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=1e-5), loss="sparse_categorical_crossentropy", metrics=["accuracy"])
		return model


	def create_EfficientNet(self, input_shape, num_classes):
		model = tf.keras.applications.EfficientNetB0((32, 32, 3), classes=num_classes, weights=None)
		model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=1e-5), loss="adam", metrics=["accuracy"])
		return model

	def create_VivaBem(self, resolution, modelType):
		RESOLUTION = resolution
		TYPE = modelType
		input_shape = (RESOLUTION, RESOLUTION, 3)
		if TYPE == "EFFICIENT_NET_B0":
			effnet = tf.keras.applications.EfficientNetB0(input_shape=input_shape, weights="imagenet", include_top=False)
			for layer in effnet.layers[:int(len(effnet.layers)*0.9)]:
				layer.trainable = False
		
			activation = 'sigmoid'
			classes = 1
			model = tf.keras.Sequential([
				effnet,
				tf.keras.layers.Flatten(),
				tf.keras.layers.Dense(512, activation='relu'),
				tf.keras.layers.Dropout(0.5),
				tf.keras.layers.Dense(256, activation='relu'),
				tf.keras.layers.Dropout(0.2),
				tf.keras.layers.Dense(classes, activation=activation)
			])
			
			model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

		elif TYPE == "EFFICIENT_NET_B1":
			effnet = tf.keras.applications.EfficientNetB1(input_shape=input_shape, weights="imagenet", include_top=False)
			for layer in effnet.layers[:int(len(effnet.layers)*0.9)]:
				layer.trainable = False
			
			activation = 'sigmoid'
			classes = 1
			model = tf.keras.Sequential([
				effnet,
				tf.keras.layers.Flatten(),
				tf.keras.layers.Dense(512, activation='relu'), 
				tf.keras.layers.Dropout(0.5),
				tf.keras.layers.Dense(256, activation='relu'), 
				tf.keras.layers.Dropout(0.2),
				tf.keras.layers.Dense(classes, activation=activation)
			])
			
			model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

		elif TYPE == "RESNET_50":
			activation = 'sigmoid'
			classes = 1	  
			resnet = tf.keras.applications.ResNet50(input_shape=input_shape, weights="imagenet", include_top=False)
			n_camadas = len(resnet.layers)
			for layer in resnet.layers:
				layer.trainable=False
			resnet.layers[n_camadas-1].trainable = True
			
			model = tf.keras.Sequential([
				resnet,
				tf.keras.layers.Flatten(),
				tf.keras.layers.Dense(512,activation='relu'), 
				tf.keras.layers.Dropout(0.5),
				tf.keras.layers.Dense(256,activation='relu'), 
				tf.keras.layers.Dropout(0.2),
				tf.keras.layers.Dense(classes, activation=activation)
			]) 

			model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

		return model
	

	def create_ImitationLearning(self, mask):
		image_size = (88, 200, 3)
		input_image = (image_size[0], image_size[1], image_size[2])
		input_speed = (1,)

		branch_config = [
		["Speed"], #Speed
		["Steer", "Gas", "Brake"], #Follow
		["Steer", "Gas", "Brake"], #Left
		["Steer", "Gas", "Brake"], #Right
		["Steer", "Gas", "Brake"] #Straight
		]

		branch_names = ['Speed', 'Follow', 'Left', 'Right', 'Straight']

		branches = []

		def conv_block(inputs, filters, kernel_size, strides):
			x = Conv2D(filters, (kernel_size, kernel_size), strides=strides, activation='relu')(inputs)
			x = MaxPooling2D(pool_size=(1, 1), strides=(1, 1))(x)
			x = BatchNormalization()(x)
			x = Dropout(0.2)(x)
			return x

		def fc_block(inputs, units):
			fc = Dense(units, activation='relu')(inputs)
			fc = Dropout(0.5)(fc)
			return fc

		xs = Input(shape=input_image, name='rgb')
		'''inputs, filters, kernel_size, strides'''
		""" Conv 1 """
		x = conv_block(xs, 32, 5, 2)
		x = conv_block(x, 32, 3, 1)
		""" Conv 2 """
		x = conv_block(x, 64, 3, 2)
		x = conv_block(x, 64, 3, 1)
		""" Conv 3 """
		x = conv_block(x, 128, 3, 2)
		x = conv_block(x, 128, 3, 1)
		""" Conv 4 """
		x = conv_block(x, 256, 3, 1)
		x = conv_block(x, 256, 3, 1)
		""" Reshape """
		x = Flatten()(x)
		""" FC1 """
		x = fc_block(x, 512)
		""" FC2 """
		x = fc_block(x, 512)
		"""Process Control"""
		""" Speed (measurements) """

		sm = Input(shape=input_speed, name='speed')
		speed = fc_block(sm, 128)
		speed = fc_block(speed, 128)
		""" Joint sensory """
		j = concatenate([x, speed])
		j = fc_block(j, 512)

		for i in range(len(branch_config)):
			if branch_config[i][0] == "Speed":
				branch_output = fc_block(x, 256)
				branch_output = fc_block(branch_output, 256)
			else:
				branch_output = fc_block(j, 256)
				branch_output = fc_block(branch_output, 256)
			fully_connected = Dense(len(branch_config[i]), name=branch_names[i])(branch_output)
			branches.append(fully_connected)

		if mask == 1: #Speed
			for branche in branches:
				if "Speed" in branche.name:
					model = Model(inputs=[xs], outputs=[branche])
					break
		elif mask == 2: #Follow
			for branche in branches:
				if "Follow" in branche.name:
					model = Model(inputs=[xs, sm], outputs=[branche])
					break
		elif mask == 3: #Left
			for branche in branches:
				if "Left" in branche.name:
					model = Model(inputs=[xs, sm], outputs=[branche])
					break
		elif mask == 4: #Right
			for branche in branches:
				if "Right" in branche.name:
					model = Model(inputs=[xs, sm], outputs=[branche])
					break
		else: #Straight
			for branche in branches:
				if "Straight" in branche.name:
					model = Model(inputs=[xs, sm], outputs=[branche])
					break
		return model

class F1Score(tf.keras.metrics.Metric):
    def __init__(self, name='f1_score', **kwargs):
        super(F1Score, self).__init__(name=name, **kwargs)
        self.precision = tf.keras.metrics.Precision()
        self.recall = tf.keras.metrics.Recall()

    def update_state(self, y_true, y_pred, sample_weight=None):
        self.precision.update_state(y_true, y_pred, sample_weight)
        self.recall.update_state(y_true, y_pred, sample_weight)

    def result(self):
        p = self.precision.result()
        r = self.recall.result()
        return 2 * ((p * r) / (p + r + tf.keras.backend.epsilon()))

    def reset_state(self):
        self.precision.reset_state()
        self.recall.reset_state()

