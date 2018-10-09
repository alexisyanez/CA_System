import sys
import numpy as np

#Create the name of the file, WithChSw-TrAD-WSM-p3-0.5s,true-#9 / 
namePrefix = "WithChSw-" 

Pr = "slotted-WSM_"
Pri= ["Ns3_p2-","Ns5-","p3-2,","p3-3,"]
WSA = ["false","true"]
IB= ["0.5s,","0.1s,"]

List1=[[],[],[]] #PDR - EED - DS
PDR=[[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]
EED=[[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]
DS=[[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]

List3= [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]


for l in range(0,4):
	t=0
	for k in range(0,2):
		for q in range(0,2):
			for i in range(0,20):
				List1=[[],[],[]] #PDR - EED - DS
				name= namePrefix + Pr + Pri[l] + IB[q] + WSA[k] +"-#" + str(i) + ".sca" 
				#print(name)
				if Pri[l] in "Ns5-":
					accT=305
				elif Pri[l] in ["Ns3_p2-","p3-2"]:
					accT=115
				else: 
					accT=95				
				f = open(name, 'r')
				temp = f.readlines()    
				j=0
				while j<len(temp):
					if "generatedWSMs" in temp[j]:  
						value = temp[j+26].split()
						Sta_T = float(value[3])
						
						value1 = temp[j+28].split()	
						Sto_T = float(value1[3])
						
						value2 = temp[j+6].split() 
						Del = float(value2[3])
						
						value3 = temp[j+7].split()
						DiS = float(value3[3]) 
						#print("Delay:"+ str(Del) + " Distancia:"+ str(DiS) +" Start_time:"+str(Sta_T) + " Stop_time:" + str(Sto_T))
						
						if Sta_T < accT and Sto_T > accT+1:
							List1[1].append(Del)
							List1[2].append(DiS/Del)
							if Del < 1 and Del > 0:								
								List1[0].append(1)
							else: 
								List1[0].append(0)
					j=j+1
								
				f.close()			
				
				#print(List1)		
				# Promedio por run 
				PDR[l][t].append(np.mean(List1[0])) # filas -> configuracion "Ns3_p2","Ns5","p3-2","p3-3" , columnas -> carga 0,5-false / 0,1-false / 0,5-true/ 0,1-true 
				EED[l][t].append(np.mean(List1[1]))
				DS[l][t].append(np.mean(List1[2]))
				#print(str(EED[l][t]) +" " + str(PDR[l][t]) + " " +str(DS[l][t]))
		
				List3[l][t].append(len(List1[2]))
			t=t+1
			
out = "MeanMetrics-Slotted"


mean_PDR=np.zeros((4,4))
mean_EED=np.zeros((4,4))
mean_DS=np.zeros((4,4))
std_PDR=np.zeros((4,4))
std_EED=np.zeros((4,4))
std_DS=np.zeros((4,4))

# filas -> configuracion "Ns3_p2","Ns5","p3-2","p3-3" , columnas -> carga 0,5-false / 0,1-false / 0,5-true/ 0,1-true 

for i in range(0,4):
	for j in range(0,4):
		mean_PDR[i][j]=np.mean(PDR[i][j])
		mean_EED[i][j]=np.mean(EED[i][j])
		mean_DS[i][j]=np.mean(DS[i][j])
		std_PDR[i][j]=np.std(PDR[i][j])
		std_EED[i][j]=np.std(EED[i][j])
		std_DS[i][j]=np.std(DS[i][j])
		
		
		
#Imprimir datos en un archivo .txt

MM1=np.matrix(mean_PDR)
MM2=np.matrix(mean_EED)
MM3=np.matrix(mean_DS)
MS1=np.matrix(std_PDR)
MS2=np.matrix(std_EED)
MS3=np.matrix(std_DS)

#print("Numero de nodos por configuracion")
print(List3)

nameOut = out+".txt" 
fw = open(nameOut, 'w')
fw.write("filas -> configuracion Ns3_p2,Ns5,p3-2,p3-3 , columnas -> carga 0,5-false / 0,1-false / 0,5-true/ 0,1-true \n")
fw.write("Promedio PDR\n")
np.savetxt(fw, MM1,fmt='%1.4f')
fw.write("\n")
fw.write("STD PDR\n")
np.savetxt(fw, MS1,fmt='%1.4f')
fw.write("\n")
fw.write("Promedios EED\n")
np.savetxt(fw, MM2,fmt='%1.4f')
fw.write("\n")
fw.write("STD EED\n")
np.savetxt(fw, MS2,fmt='%1.4f')
fw.write("\n")
fw.write("Promedios DS\n")
np.savetxt(fw, MM3,fmt='%1.4f')
fw.write("\n")
fw.write("STD DS \n")
np.savetxt(fw, MS3,fmt='%1.4f')
fw.write("\n")
#fw.write("Numero de nodos x config\n")
#np.savetxt(fw, num )
#fw.write("/n")
fw.close()	




Pr = "TrAD-"
Pri = ["WSM-p3-","WSM-p2-","WSM-"]
WSA = ["false","true"]
IB= ["0.5s,","0.1s,"]

List1=[[],[],[]] #PDR - EED - DS
PDR=[[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]
EED=[[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]
DS=[[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]

List3= [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]

for l in range(0,3):
	t=0
	for k in range(0,2):
		for q in range(0,2):
			for i in range(0,20):
				List1=[[],[],[]] #PDR - EED - DS
				name= namePrefix + Pr + Pri[l] + IB[q] + WSA[k] +"-#" + str(i) + ".sca" 
				#print(name)
				if l == 0:
					accT=95
				elif l == 1:
					accT=115
				else: 
					accT=305				
				f = open(name, 'r')
				temp = f.readlines()    
				j=0
				while j<len(temp):
					if "generatedWSMs" in temp[j]:  
						value = temp[j+26].split()
						Sta_T = float(value[3])
						
						value1 = temp[j+28].split()	
						Sto_T = float(value1[3])
						
						value2 = temp[j+6].split() 
						Del = float(value2[3])
						#print(Del)
						value3 = temp[j+7].split()
						DiS = float(value3[3]) 
						
						if Sta_T < accT and Sto_T > accT+1:
							List1[1].append(Del)
							List1[2].append(DiS/Del)
							if Del < 1 and Del > 0:								
								List1[0].append(1)
							else: 
								List1[0].append(0)
					j=j+1
								
				f.close()			
						
				# Promedio por run 
				PDR[l][t].append(np.mean(List1[0])) # filas -> configuracion "Ns3_p2","Ns5","p3-2","p3-3" , columnas -> carga 0,5-false / 0,1-false / 0,5-true/ 0,1-true 
				EED[l][t].append(np.mean(List1[1]))
				DS[l][t].append(np.mean(List1[2]))
				
				#Sx=[np.std(list1[0]), np.std(list1[1]), np.std(list1[1])]	
				#List2[l][k][j].append(Mx)
				#List2[1][l][k][j].append(Sx)
				List3[l][t].append(len(List1[2]))
			t=t+1
			
out = "MeanMetrics-TrAD"


mean_PDR=np.zeros((3,4))
mean_EED=np.zeros((3,4))
mean_DS=np.zeros((3,4))
std_PDR=np.zeros((3,4))
std_EED=np.zeros((3,4))
std_DS=np.zeros((3,4))

# filas -> configuracion "Ns3_p2","Ns5","p3-2","p3-3" , columnas -> carga 0,5-false / 0,1-false / 0,5-true/ 0,1-true 

for i in range(0,3):
	for j in range(0,4):
		mean_PDR[i][j]=np.mean(PDR[i][j])
		mean_EED[i][j]=np.mean(EED[i][j])
		mean_DS[i][j]=np.mean(DS[i][j])
		std_PDR[i][j]=np.std(PDR[i][j])
		std_EED[i][j]=np.std(EED[i][j])
		std_DS[i][j]=np.std(DS[i][j])
		
		
		
#Imprimir datos en un archivo .txt

MM1=np.matrix(mean_PDR)
MM2=np.matrix(mean_EED)
MM3=np.matrix(mean_DS)
MS1=np.matrix(std_PDR)
MS2=np.matrix(std_EED)
MS3=np.matrix(std_DS)

#num=np.matrix(List3)
#print("Numero de nodos por configuracion TrAD")
print(List3)

nameOut = out+".txt" 
fw = open(nameOut, 'w')
fw.write("filas -> configuracion WSM-p3- , WSM-p2- , WSM- , columnas -> carga 0,5-false / 0,1-false / 0,5-true/ 0,1-true \n")
fw.write("Promedio PDR\n")
np.savetxt(fw, MM1,fmt='%1.4f')
fw.write("\n")
fw.write("STD PDR\n")
np.savetxt(fw, MS1,fmt='%1.4f')
fw.write("\n")
fw.write("Promedios EED\n")
np.savetxt(fw, MM2,fmt='%1.4f')
fw.write("\n")
fw.write("STD EED\n")
np.savetxt(fw, MS2,fmt='%1.4f')
fw.write("\n")
fw.write("Promedios DS\n")
np.savetxt(fw, MM3,fmt='%1.4f')
fw.write("\n")
fw.write("STD DS \n")
np.savetxt(fw, MS3,fmt='%1.4f')
fw.write("\n")
#fw.write("Numero de nodos x config\n")
#np.savetxt(fw, num )
#fw.write("/n")
fw.close()
