import sys
import numpy as np
import tensorflow as tf
import h2o

from h2o.automl import H2OAutoML
from tensorflow import keras


from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.utils.multiclass import unique_labels

#############################################
# Extraer datos desde vectores para BAJA densidad
##############################################
C=['C1','C2','C3']
# CBR: Channel Busy Ratio, NBR: Normalize Broadcast Received, NTIB: Normalize Times Into Back-Off
Met=['CBR','NBR','NTIB']
Y=[]
X=[[],[],[]]           
for i in C:
	for j in Met:
		exec(open(j+'_'+i+'_LowDen.py').read())
		for h in opp_results:
			for g in opp_results[h]['vectors']:
				f=g['value']
				for d in f:
				#X[Met.index(j)]=[X[Met.index(j)],f]
					X[Met.index(j)].append(d)
	
	a=C.index(i)
	l=[a]
	l=l*(len(X[0])-len(Y))
	print(len(X[0]))
	print(len(l))
	Y+=l
	print(len(Y))

########################################
### Trasponer la data vector para Keras
X2=list(map(list, zip(*X)))
########################################
### Desde acá la data esta en tipo Lista

DATA=[X2,Y]

#X1=X2
#Y1=Y

# Probando con H2o
h2o.init()

#train_dataset =train_dataset.as_data_frame()

# Import a sample binary outcome training set into H2O
train = DATA #h2o.import_file("https://s3.amazonaws.com/erin-data/higgs/higgs_train_10k.csv")

# Identify predictors and response
x = X2
y = Y
#x.remove(y)

# For binary classification, response should be a factor
y = tf.one_hot(y, depth=3)

print(type(x))
print(x[0])
print(type(y))
print(y[0])

aml = H2OAutoML(max_runtime_secs = 30, sort_metric = "logloss")
aml.train(x = x, y = y,
          training_frame = train)

# View the AutoML Leaderboard
lb = aml.leaderboard

print(lb)


########################################
### Conversion de la Data a np.array
X1=np.asarray(X2)
Y1=np.asarray(Y)







########################################
### Plot Scatters

#x4=['CBR' ,'NBR', 'NTIB']
x4=[]
for i in X1:
	x4.append(['CBR', 'NBR', 'NTIB'])			
x4 = np.asarray(x4)

#plt.scatter(xx,yy)

colors = ("red", "green", "blue")
groups = ("CBR", "NBR", "NTIB")
g1=(x4[:,0],X1[:,0])
g2=(x4[:,1],X1[:,1])
g3=(x4[:,2],X1[:,2])
data=(g1,g2,g3)
#data=tuple(data)

#print("Targets:   {}".format(.shape))  
# Create plot
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1, facecolor="1.0")

for data, color, group in zip(data, colors, groups):
	x, y = data
	ax.scatter(x, y, alpha=0.8, c=color, edgecolors='none', s=30, label=group)
plt.title('Matplot scatter plot')
plt.legend(loc=2)

plt.show()

X1=np.expand_dims(X1,-1)


########################################
### Funciones para Keras

	
def preprocess(x, y):
  x = tf.cast(x, tf.float32) #/ 255.0
  y = tf.cast(y, tf.int64)

  return x, y
	
# Función para crear base de datos	
def create_dataset(xs, ys, n_classes):
  ys = tf.one_hot(ys, depth=n_classes)
  return tf.data.Dataset.from_tensor_slices((xs, ys)) \
    .map(preprocess) \
    .shuffle(len(ys)) \
    .batch(128)

########################################
### Base da datos para Keras

# Obtener porcentaje de la base de datos				
x_train, x_test, y_train, y_test = train_test_split(X1,Y1,test_size=0.3,random_state=42)	

# Crear base de datos				
train_dataset = create_dataset(x_train, y_train,3)
val_dataset = create_dataset(x_test, y_test,3)


########################################
### Construir modelo Keras


model = keras.Sequential([
    keras.layers.Reshape(target_shape=(1*3 ,), input_shape=(3, 1)),
    keras.layers.Dense(units=9, activation='sigmoid'),
    keras.layers.Dense(units=6, activation='sigmoid'),
   # keras.layers.Dense(units=6, activation='sigmoid'),
    keras.layers.Dense(units=3, activation='softmax')
])

model.compile(optimizer='adam', # 'sgd', 
              loss='binary_crossentropy', #'mean_squared_error', #loss=tf.losses.CategoricalCrossentropy(from_logits=True),
              metrics=['accuracy'])


history = model.fit(
    train_dataset.repeat(), 
    epochs=15, 
    steps_per_epoch=500,
    validation_data=val_dataset.repeat(), 
    validation_steps=2
)

########################################
### Guardar modelo Keras

# save model and architecture to single file
model.save("model_LowDen.h5")
print("Saved model to disk")

predictions = model.predict(x_test)

predictions=np.argmax(predictions,axis=1)

########################################
### Plot confusion matrix

#print("Expected: (num_samples, timesteps, channels)")
#print("Sequences: {}".format(np.argmax(predictions).shape))
#print("Targets:   {}".format(y_test.shape))   

#plt.show(block=True)

#print('confision matrix')

#plt.scatter(y_test, predictions)
#plt.xlabel('True Values')
#plt.ylabel('Predictions')
#plt.show()

def plot_confusion_matrix(y_true, y_pred, classes,
                          normalize=False,
                          title=None,
                          cmap=plt.cm.Blues):
    """
    This function prints and plots the confusion matrix.
    Normalization can be applied by setting `normalize=True`.
    """
    if not title:
        if normalize:
            title = 'Normalized confusion matrix'
        else:
            title = 'Confusion matrix, without normalization'

    # Compute confusion matrix
    cm = confusion_matrix(y_true, y_pred)
    # Only use the labels that appear in the data
    classes = list(unique_labels(y_true, y_pred))
    if normalize:
        cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
        print("Normalized confusion matrix")
    else:
        print('Confusion matrix, without normalization')

    print(cm)

    fig, ax = plt.subplots()
    im = ax.imshow(cm, interpolation='nearest', cmap=cmap)
    ax.figure.colorbar(im, ax=ax)
    # We want to show all ticks...
    ax.set(xticks=np.arange(cm.shape[1]),
           yticks=np.arange(cm.shape[0]),
           # ... and label them with the respective list entries
           xticklabels=classes, yticklabels=classes,
           title=title,
           ylabel='True label',
           xlabel='Predicted label')

    # Rotate the tick labels and set their alignment.
    plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
             rotation_mode="anchor")

    # Loop over data dimensions and create text annotations.
    fmt = '.2f' if normalize else 'd'
    thresh = cm.max() / 2.
    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            ax.text(j, i, format(cm[i, j], fmt),
                    ha="center", va="center",
                    color="white" if cm[i, j] > thresh else "black")
    fig.tight_layout()
    return ax

target_names = ['BSM:2HZ' 'BSM:10Hz' 'BSM:10Hz+WSA:1Hz']

#plot_confusion_matrix(tf.cast(y_test,tf.int64),tf.cast(predictions,tf.int64),classes=target_names,title='Confusion matrix, without normalization')

#plt.show()

#~ print('Classification Report')
#~ clases = classification_report(tf.cast(y_test,tf.int64), predictions, target_names=target_names)
#~ plt.show(clases) 




##############################################
# Extraer datos desde vectores para ALTA densidad
##############################################

C=['C1','C2','C3']
# CBR: Channel Busy Ratio, NBR: Normalize Broadcast Received, NTIB: Normalize Times Into Back-Off
Met=['CBR','NBR','NTIB']
Y=[]
X=[[],[],[]]           
for i in C:
	for j in Met:
		exec(open(j+'_'+i+'_HighDen.py').read())
		for h in opp_results:
			for g in opp_results[h]['vectors']:
				f=g['value']
				for d in f:
				#X[Met.index(j)]=[X[Met.index(j)],f]
					X[Met.index(j)].append(d)
	
	a=C.index(i)
	l=[a]
	l=l*(len(X[0])-len(Y))
#	print(len(X[0]))
#	print(len(l))
	Y+=l
#	print(len(Y))


#print(len(X[1]))
#print(len(X[0]))
#print(len(Y))
#print('dimension of feature: '+str(len(X)) + ','+str(len(X[0])))
#print('dimension of label: '+str(len(Y)) + ',1')
X2=list(map(list, zip(*X)))
#print('re-dimension of feature: '+str(len(X2)) + ','+str(len(X2[0])))

#X1=X2
#Y1=Y


X1=np.asarray(X2)
Y1=np.asarray(Y)

X1=np.expand_dims(X1,-1)

	
def preprocess(x, y):
  x = tf.cast(x, tf.float32) #/ 255.0
  y = tf.cast(y, tf.int64)

  return x, y
	
# Función para crear base de datos	
def create_dataset(xs, ys, n_classes):
  ys = tf.one_hot(ys, depth=n_classes)
  return tf.data.Dataset.from_tensor_slices((xs, ys)) \
    .map(preprocess) \
    .shuffle(len(ys)) \
    .batch(128)
	
# Obtener porcentaje de la base de datos				
x_train, x_test, y_train, y_test = train_test_split(X1,Y1,test_size=0.3,random_state=42)	

# Crear base de datos				
train_dataset = create_dataset(x_train, y_train,3)
val_dataset = create_dataset(x_test, y_test,3)

model = keras.Sequential([
    keras.layers.Reshape(target_shape=(1*3 ,), input_shape=(3, 1)),
    keras.layers.Dense(units=15, activation='sigmoid'),
    keras.layers.Dense(units=12, activation='sigmoid'),
    keras.layers.Dense(units=9, activation='sigmoid'),
    keras.layers.Dense(units=3, activation='softmax')
])

model.compile(optimizer='adam', # 'sgd', 
              loss='binary_crossentropy', #'mean_squared_error', #loss=tf.losses.CategoricalCrossentropy(from_logits=True),
              metrics=['accuracy'])

history = model.fit(
    train_dataset.repeat(), 
    epochs=15, 
    steps_per_epoch=500,
    validation_data=val_dataset.repeat(), 
    validation_steps=2
)

# save model and architecture to single file
model.save("model_HighDen.h5")
print("Saved model to disk")

predictions = model.predict(x_test)

predictions=np.argmax(predictions,axis=1)


target_names = ['BSM:2HZ' 'BSM:10Hz' 'BSM:10Hz+WSA:1Hz']

