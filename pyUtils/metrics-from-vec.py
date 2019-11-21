import sys
import numpy as np
import tensorflow as tf
from tensorflow import keras
from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split

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
    keras.layers.Dense(units=9, activation='sigmoid'),
    keras.layers.Dense(units=6, activation='sigmoid'),
    #keras.layers.Dense(units=3, activation='sigmoid'),
    keras.layers.Dense(units=3, activation='softmax')
])

model.compile(optimizer='adam', 
              loss=tf.losses.CategoricalCrossentropy(from_logits=True),
              metrics=['accuracy'])

history = model.fit(
    train_dataset.repeat(), 
    epochs=10, 
    steps_per_epoch=500,
    validation_data=val_dataset.repeat(), 
    validation_steps=2
)

predictions = model.predict(x_test)

predictions=np.argmax(predictions,axis=1)

print("Expected: (num_samples, timesteps, channels)")
print("Sequences: {}".format(np.argmax(predictions).shape))
print("Targets:   {}".format(y_test.shape))   

plt.show(block=True)


plt.scatter(y_test, predictions)
plt.xlabel('True Values')
plt.ylabel('Predictions')

plt.show() 
