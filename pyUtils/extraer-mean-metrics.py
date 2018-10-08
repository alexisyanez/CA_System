import sys
import numpy as np

#Create the name of the file, WithChSw-TrAD-WSM-p3-0.5s,true-#9 / 
namePrefix = "WithChSw-" 

Pr = "slotted-WSM_"
Pri= ["Ns3_p2","Ns5","p3-2","p3-3"]
WSA = ["false","true"]
IB= ["0,5s,","0.1s,"]

List1=[[],[],[]] #PDR - EED - DS
List2= [[[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]]],[[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]]]]
List3= [[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]]]

for l in range (0,4)
	for k in range(0,2)
		for j in range(0,2)
			for i in range(0,20):
				List1=[[],[],[]] #PDR - EED - DS
				name= namePrefix + Pr + Pri(l) + IB(j) + WSA(k) +"-#" + str(i) + ".sca" 
				if Pri(l) in "Ns5":
					accT=305
				else if Pri(l) in ["Ns3_p2","p3-2"]:
					accT=115
				else 
					accT=95				
				f = open(name, 'r')
				temp = f.readlines()    
				while j<len(temp):
					if "generatedWSMs" in temp[j]:  
						value = temp[j+26].split()
						Sta_T = float(value[3])
						
						value1 = temp[j+27].split()	
						Ttl_T = float(value1[3])
						
						value2 = temp[j+6].split() 
						Del = float(value2[3])
						
						value3 = temp[j+7].split()
						DiS = float(value3[3]) 
						
						if Sta_T > accT and Ttl_T > 1:
							List1[1].append(Del)
							List1[2].append(DiS/Del)
							if Del < 1								
								List1[0].append(1)
					j=j+1
								
				f.close()
			
				Mx=[np.mean(list1[0]), np.mean(list1[1]), np.mean(list1[1])]		
				Sx=[np.std(list1[0]), np.std(list1[1]), np.std(list1[1])]	
				List2[0][l][k][j].append(Mx)
				List2[1][l][k][j].append(Sx)
				List3[l][k][j].append(len(list1[2]))
				
			
			


Pr = "TrAD-WSM-"
Pri = ["p3","p2",""]
WSA = ["false","true"]
IB= ["0.1s,","0,5s,"]


List4=[[],[],[]] #PDR - EED - DS
List5= [[[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]]],[[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]]]]
List6= [[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]],[[[],[]],[[],[]]]]

for l in range (0,4)
	for k in range(0,2)
		for m in range(0,2)
			for i in range(0,20):
				name= namePrefix + Pr + Pri(l) + IB(m) + WSA(k) +"-#" + str(i) + ".sca" 
				if Pri(l) in "p3":
					accT=95
				else if Pri(l) in "p2":
					accT=115
				else 
					accT=305				
				f = open(name, 'r')
				temp = f.readlines()    
				while j<len(temp):
					if "generatedWSMs" in temp[j]:  
						value = temp[j+26].split()
						Sta_T = float(value[3])
						
						value1 = temp[j+27].split()	
						Ttl_T = float(value1[3])
						
						value2 = temp[j+6].split() 
						Del = float(value2[3])
						
						value3 = temp[j+7].split()
						DiS = float(value3[3]) 
						
						if Sta_T > accT and Ttl_T > 1:
							List4[1].append(Del)
							List4[2].append(DiS/Del)
							if Del < 1 and Del > 0								
								List4[0].append(1)
							else
								List4[0].append(0)
					j=j+1
				
				List5[0][l][k][j].append(np.mean(list4))
				List5[1][l][k][j].append(np.std(list4)))
				List6[l][k][j].append(np.mean(list4(0)))								
				f.close()
					




#Extract the packets received from the .sca file  , $0=0.05, $1=0.05, $2=8"
out = "MeanMetrics-Slotted"

   
met2=np.zeros((2,29))
Var2=np.zeros((2,29))


#print(str(np.mean(ListG[0][0])))
for i in range(0,29):
	Var1[0][i]=np.mean(ListG1[0][i])
	Var1[1][i]=np.mean(ListG1[1][i])
	
for i in range(0,29):
	Var2[0][i]=np.mean(ListG2[0][i])
	Var2[1][i]=np.mean(ListG2[1][i])
		
	
	
#Imprimir datos en un archivo .txt
mat=np.matrix(Var1)
mat2=np.matrix(Var2)	

nameOut = out+"Var05.txt" 
fw = open(nameOut, 'w')
fw.write('Promedios (fila 1) y STD (fila 2) ACC para Var 0.05\n')
np.savetxt(fw, mat)
fw.close()	



nameOut = out+"STD.txt" 
fw = open(nameOut, 'w')
fw.write('Promedios (fila 1) y STD (fila 2) ACC para Var 0.2n \n')
np.savetxt(fw, mat2)
fw.close()
