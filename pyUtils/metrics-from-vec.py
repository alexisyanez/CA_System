import sys
import numpy as np
import tensorflow as tf
from tensorflow import keras

from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.utils.multiclass import unique_labels

# Extraer datos desde vectores

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


print(len(X[1]))
print(len(X[0]))
print(len(Y))
print('dimension of feature: '+str(len(X)) + ','+str(len(X[0])))
print('dimension of label: '+str(len(Y)) + ',1')
X2=list(map(list, zip(*X)))
print('re-dimension of feature: '+str(len(X2)) + ','+str(len(X2[0])))

#X1=X2
#Y1=Y


X1=np.asarray(X2)
Y1=np.asarray(Y)

X1=np.expand_dims(X1,-1)
print(type(X1))

print('primer valor de X')
print(X1[0])
print('primer valor de Y')
print(Y1[0])

print("Expected: (num_samples, timesteps, channels)")
print("Sequences: {}".format(X1.shape))
print("Targets:   {}".format(Y1.shape))   
	

#X1=np.expand_dims(X1,-1)
#Y1=np.expand_dims(Y1,-1)

#print("Expected: (num_samples, timesteps, channels)")
#print("Sequences: {}".format(X1.shape))
#print("Targets:   {}".format(Y1.shape))   

#~ def my_func(arg):
  #~ arg = tf.convert_to_tensor(arg, dtype=tf.float32)
  #~ return tf.matmul(arg, arg) + arg
  
#~ X1=my_func(X1)
#~ Y1=my_func(Y1)
	
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
    keras.layers.Dense(units=12, activation='sigmoid'),
    keras.layers.Dense(units=9, activation='sigmoid'),
    keras.layers.Dense(units=6, activation='sigmoid'),
    keras.layers.Dense(units=3, activation='softmax')
])

model.compile(optimizer='adam', 
              loss='binary_crossentropy',#loss=tf.losses.CategoricalCrossentropy(from_logits=True),
              metrics=['accuracy'])

history = model.fit(
    train_dataset.repeat(), 
    epochs=15, 
    steps_per_epoch=500,
    validation_data=val_dataset.repeat(), 
    validation_steps=2
)

# save model and architecture to single file
model.save("model.LowDen")
print("Saved model to disk")

predictions = model.predict(x_test)

predictions=np.argmax(predictions,axis=1)

print("Expected: (num_samples, timesteps, channels)")
print("Sequences: {}".format(np.argmax(predictions).shape))
print("Targets:   {}".format(y_test.shape))   

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

plot_confusion_matrix(tf.cast(y_test,tf.int64),tf.cast(predictions,tf.int64),classes=target_names,title='Confusion matrix, without normalization')
#plot_confusion_matrix(matrix)
plt.show()

#~ print('Classification Report')
#~ clases = classification_report(tf.cast(y_test,tf.int64), predictions, target_names=target_names)
#~ plt.show(clases) 


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
	print(len(X[0]))
	print(len(l))
	Y+=l
	print(len(Y))


print(len(X[1]))
print(len(X[0]))
print(len(Y))
print('dimension of feature: '+str(len(X)) + ','+str(len(X[0])))
print('dimension of label: '+str(len(Y)) + ',1')
X2=list(map(list, zip(*X)))
print('re-dimension of feature: '+str(len(X2)) + ','+str(len(X2[0])))

#X1=X2
#Y1=Y


X1=np.asarray(X2)
Y1=np.asarray(Y)

X1=np.expand_dims(X1,-1)
print(type(X1))

print('primer valor de X')
print(X1[0])
print('primer valor de Y')
print(Y1[0])

print("Expected: (num_samples, timesteps, channels)")
print("Sequences: {}".format(X1.shape))
print("Targets:   {}".format(Y1.shape))   
	

#X1=np.expand_dims(X1,-1)
#Y1=np.expand_dims(Y1,-1)

#print("Expected: (num_samples, timesteps, channels)")
#print("Sequences: {}".format(X1.shape))
#print("Targets:   {}".format(Y1.shape))   

#~ def my_func(arg):
  #~ arg = tf.convert_to_tensor(arg, dtype=tf.float32)
  #~ return tf.matmul(arg, arg) + arg
  
#~ X1=my_func(X1)
#~ Y1=my_func(Y1)
	
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
    keras.layers.Dense(units=12, activation='sigmoid'),
    keras.layers.Dense(units=9, activation='sigmoid'),
    keras.layers.Dense(units=6, activation='sigmoid'),
    keras.layers.Dense(units=3, activation='softmax')
])

model.compile(optimizer='adam', 
              loss='binary_crossentropy',#loss=tf.losses.CategoricalCrossentropy(from_logits=True),
              metrics=['accuracy'])

history = model.fit(
    train_dataset.repeat(), 
    epochs=15, 
    steps_per_epoch=500,
    validation_data=val_dataset.repeat(), 
    validation_steps=2
)

# save model and architecture to single file
model.save("model.HighDen")
print("Saved model to disk")

predictions = model.predict(x_test)

predictions=np.argmax(predictions,axis=1)

print("Expected: (num_samples, timesteps, channels)")
print("Sequences: {}".format(np.argmax(predictions).shape))
print("Targets:   {}".format(y_test.shape))   

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

plot_confusion_matrix(tf.cast(y_test,tf.int64),tf.cast(predictions,tf.int64),classes=target_names,title='Confusion matrix, without normalization')
#plot_confusion_matrix(matrix)
plt.show()

#~ print('Classification Report')
#~ clases = classification_report(tf.cast(y_test,tf.int64), predictions, target_names=target_names)
#~ plt.show(clases) 
