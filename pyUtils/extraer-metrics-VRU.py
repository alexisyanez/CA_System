import sys
import numpy as np

#Create the name of the file, Ped_Crossing-BL-DEN=23500s,BL=0.1s,0.1s,0.1s,0.1s,23510s-#0.sca
Pathresults= "/home/ayanez/CA_System/src/networks/MoST_Scenario/results/"

#Pathresults= "/home/aware/git/CA_System/src/networks/MoST_Scenario/results/"
namePrefix = "Ped_Crossing-"

#Conf = "BL-DEN="
#Conf = "MovinPed-200bytes-DEN=" 
#Conf = "OnStreet-DEN=" 
#Ped_Crossing-MultipleTx-DEN=28500s,28510s-#0.sca

Conf = "BL-NoObstacle-S4-DEN="
#Conf = "OnStreet-200bytes-DEN="
#Conf = "MultipleTx-200bytes-DEN="

#22406s,22537s,22887s,23056s
#22409s,22540s,22890s,23059s
#20599s,22330s,22113s,23916s
DEN= ["20599s,","22330s,","22113s,","23916s,"]
Interval = ["1s,","0.5s,","0.2s,","0.1s,"]
END= ["20602s","22333s","22116s","23919s"]

Total_Nodes = [10,20,28,37]
bec_freq = [1,2,5,10]


MeanRunsPDR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunPDR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
MeanRunsCBR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunCBR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

RealSendPkt = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
DesiredSendPkt = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

MeanPDR2 = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDPDR2 = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz


for l in range(0,4):
	for k in range(0,4):
		List1 = [[],[]] #PDR - CBR
		PDR2 = [] #New PDR
		Suma_Send = []
		Desired_Send = []
		for i in range(0,5): #(0,10):
			PKT_Total_Rec = []
			PKT_Total_Send = []
			#List1 = [[],[]]
			name= Pathresults + namePrefix + Conf +  DEN[l] + "BL="+ Interval[k] + Interval[k] + Interval[k] + Interval[k] + END[l]  +"-#" + str(i) + ".sca" 

			#CBR =[];
			f = open(name, 'r')
			temp = f.readlines()    
			j=0
			while j<len(temp):
				if "generatedWSMs" in temp[j]:  
					value = temp[j+24].split()
					Sta_T = float(value[3])
					
					value5 = temp[j+25].split()
					Total_T = float(value5[3])

					value1 = temp[j+26].split()	
					Sto_T = float(value1[3])
													
					value2 = temp[j+14].split() 
					PKT_send = float(value2[3])
					
					value3 = temp[j+3].split()
					PKT_Rec = float(value3[3]) 
					
					value4 = temp[j+23].split()
					Busy_T = float(value4[3]) 
					
					#SenNumber = float(value4[3]) 
					#CBR.append(SenNumber)
					
					#print("Delay:"+ str(Del) + " Distancia:"+ str(DiS) +" Start_time:"+str(Sta_T) + " Stop_time:" + str(Sto_T))
					delta_t=Sto_T-Sta_T
					#if Total_T > 0 and PKT_Rec>0:
						#PDR = 1-(PKT_Lost/(PKT_Rec+PKT_Lost))
					PKT_Total_Rec.append(PKT_Rec)
					PKT_Total_Send.append(PKT_send)
					if Total_T > 0:
                                            CBR = Busy_T/Total_T
                                            List1[1].append(CBR)
                                            #List1[0].append(PDR)

				j=j+1
			f.close()
			Suma_Send.append(sum(PKT_Total_Send))

			Num_Nodes = Total_Nodes[l] #sum(PKT_Total_Rec)

			Desired_Send.append(bec_freq[k]*3*Num_Nodes)

			PDR = sum(PKT_Total_Rec)/(sum(PKT_Total_Send*Num_Nodes)) #(bec_freq[k]*10*Num_Nodes)
			List1[0].append(PDR)

			PDR_n = sum(PKT_Total_Rec)/(bec_freq[k]*3*Num_Nodes*Num_Nodes) 
			PDR2.append(PDR_n)

		MeanRunsPDR[l][k].append(np.mean(List1[0]))  
		STDRunPDR[l][k].append(np.std(List1[0])) 
#[k] en lugar de cero
		MeanRunsCBR[l][k].append(np.mean(List1[1]))  
		STDRunCBR [l][k].append(np.std(List1[1]))

		DesiredSendPkt[l][k].append(np.mean(Desired_Send))
		RealSendPkt[l][k].append(np.mean(Suma_Send))

		MeanPDR2[l][k].append(np.mean(PDR2))
		STDPDR2[l][k].append(np.std(PDR2))
 
out = "MeanMetrics-BL-NoObstacle-S4"
#out = "MeanMetrics-MovinPed-200bytes-newPDR"
#out = "MeanMetrics-OnStreet"
#out = "MeanMetrics-MultipleTx-200bytes-S4"
#out = "MeanMetrics-OnStreet-200bytes-newPDR"

#Imprimir datos en un archivo .txt

#MM1=np.asarray(MeanRunsPDR)
#MM2=np.asarray(MeanRunsCBR)
#MS1=np.asarray(STDRunPDR)
#MS2=np.asarray(STDRunCBR)

print("MeanRuns PDR: "+ str(MeanRunsPDR))

nameOut = out+".txt" 
fw = open(nameOut, 'w')
fw.write("Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz \n Cálculo realizado con paquetes generados en la capa MAC \n")
fw.write("Promedio PDR:\n")
for line in  MeanRunsPDR:
    fw.write(str(line))
    fw.write("\n")
fw.write("Promedio CBR:\n")
for line in MeanRunsCBR:
    fw.write(str(line))
    fw.write("\n")
fw.write("STD PDR:\n")
for line in  STDRunPDR:
    fw.write(str(line))
    fw.write("\n")
fw.write("STD CBR:\n")
for line in STDRunCBR:
    fw.write(str(line))
    fw.write("\n")
fw.write("Número estimado real de paquetes enviados\n")
for line in RealSendPkt:
    fw.write(str(line))
    fw.write("\n")
fw.write("Número deseado de paquetes enviados\n")
for line in DesiredSendPkt:
    fw.write(str(line))
    fw.write("\n")

fw.write("Cálculo realizado con estimación de los paquetes enviados deseados \n Promedio CBR:\n")
for line in MeanPDR2:
    fw.write(str(line))
    fw.write("\n")
fw.write("STD PDR:\n")
for line in  STDPDR2:
    fw.write(str(line))
    fw.write("\n")

#np.savetxt(fw, MM1,fmt='%1.4f')
#fw.write("\n")
#fw.write("STD PDR\n")
#np.savetxt(fw, MS1,fmt='%1.4f')
#fw.write("\n")
#fw.write("Promedios CBR\n")
#np.savetxt(fw, MM2,fmt='%1.4f')
#fw.write("\n")
#fw.write("STD DS \n")
#np.savetxt(fw, MS2,fmt='%1.4f')
#fw.write("\n")
#fw.write("Numero de nodos x config\n")
#np.savetxt(fw, num )
#fw.write("/n")
fw.close()	
