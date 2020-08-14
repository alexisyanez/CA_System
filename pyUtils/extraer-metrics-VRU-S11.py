import sys
import numpy as np


Pathresults= "/home/ayanez/CA_System/src/networks/MoST_Scenario/results/"

#Pathresults= "/home/aware/git/CA_System/src/networks/MoST_Scenario/results/"
namePrefix = "Ped_Crossing-"

#Conf = "MovinPed-S11-"
Conf = "BL-Obstacle-S11-"
#Conf = "OnStreet-S11-"
#Conf = "MultipleTx-S11-"
#Conf = "BL-NoObstacle-S11-"

#Ped_Crossing-BL-Obstacle-S11-DEN=xmldoc(#22MoST#_ped3.launchd.xml#22),290s,310s,BL=0.1s-#0.sca
#Ped_Crossing-BL-Obstacle-S11-DEN=xmldoc(#22MoST#_ped4.launchd.xml#22),130s,150s,BL=0.1s-#0.sca

DEN = ["DEN=xmldoc(#22MoST#_ped3.launchd.xml#22),290s,310s,BL=","DEN=xmldoc(#22MoST#_ped4.launchd.xml#22),130s,150s,BL="]


Interval = ["1s","0.5s","0.2s","0.1s"]

MeanRunsPDR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunPDR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
MeanRunsCBR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunCBR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

RealSendPkt = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
DesiredSendPkt = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] #wFilas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

for l in range(0,2):	
	for k in range(0,4):
		List1 = [[],[]] #PDR - CBR
		PDR2 = [] #New PDR
		Suma_Send = []
		Desired_Send = []
		for i in range(0,5): #(0,10):
			comp=[[],[],[]]
			PKT_Total_Rec = []
			PKT_Total_Send = []
			#List1 = [[],[]]
			name= Pathresults + namePrefix + Conf + DEN[l] + Interval[k] + "-#" + str(i) + ".sca" #  "BL="+ Interval[k]+"," + Interval[k]+","+ Interval[k]+"," + Interval[k]  +"-#" + str(i) + ".sca" #DEN[l] + "BL="+ Interval[k] + END[l]  +"-#" + str(i) + ".sca" 

			#CBR =[];
			f = open(name, 'r')
			temp = f.readlines()
			j=0
			while j<len(temp):
				if "generatedWSMs" in temp[j]:
					value = temp[j+25].split()
					Sta_T = float(value[3])

					value5 = temp[j+26].split()
					Total_T = float(value5[3])

					value1 = temp[j+27].split()
					Sto_T = float(value1[3])

					value2 = temp[j+15].split()
					PKT_send = float(value2[3])

					value3 = temp[j+4].split()
					PKT_Rec = float(value3[3])

					value4 = temp[j+24].split()
					Busy_T = float(value4[3])

					value5 = temp[j+18].split()
					PKT_Lost = float(value5[3])

					#SenNumber = float(value4[3])
					#CBR.append(SenNumber)
					#print("Delay:"+ str(Del)w + " Distancia:"+ str(DiS) +" Start_time:"+str(Sta_T) + " Stop_time:" + str(Sto_T))
					delta_t=Sto_T-Sta_T

					#if Total_T > 0 and PKT_Rec>0:
					#    CBR = Busy_T/Total_T
					#    PDR = 1-(PKT_Lost/(PKT_Rec+PKT_Lost))
					#    List1[1].append(CBR)
					#    List1[0].append(PDR)

					PKT_Total_Rec.append(PKT_Rec)
					PKT_Total_Send.append(PKT_send)
					if delta_t > 0:
						CBR = Busy_T/delta_t
						PDR = 1-(PKT_Lost/(PKT_Rec+PKT_Lost))
						List1[1].append(CBR)
						List1[0].append(PDR)

				j=j+1
			f.close()
			#Suma_Send.append(sum(PKT_Total_Send))

			#Num_Nodes = Total_Nodes #[l] #sum(PKT_Total_Rec)

			#Desired_Send.append(bec_freq[k]*20*Num_Nodes)

			#PDR = sum(PKT_Total_Rec)/(sum(PKT_Total_Send)*Num_Nodes) #(bec_freq[k]*10*Num_Nodes)
			#List1[0].append(PDR)

			#PDR_n = sum(PKT_Total_Rec)/(bec_freq[k]*20*Num_Nodes*Num_Nodes) 
			#PDR2.append(PDR_n)
		
		MeanRunsPDR[l][k].append(np.mean(List1[0]))  
		STDRunPDR[l][k].append(np.std(List1[0])) 
	#[k] en lugar de cero
		MeanRunsCBR[l][k].append(np.mean(List1[1]))  
		STDRunCBR [l][k].append(np.std(List1[1]))

		#DesiredSendPkt[l][k].append(np.mean(Desired_Send))
		#RealSendPkt[l][k].append(np.mean(Suma_Send))

		#MeanPDR2[l][k].append(np.mean(PDR2))
		#STDPDR2[l][k].append(np.std(PDR2))

out = "MeanMetrics-BL-Obstacle-S11"
#out = "MeanMetrics-MovinPed-S11"
#out = "MeanMetrics-OnStreet-S11"
#out = "MeanMetrics-MultipleTx-S11"
#out = "MeanMetrics-BL-NoObstacle-S11"


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
#~ fw.write("Número estimado real de paquetes enviados\n")
#~ for line in RealSendPkt:
    #~ fw.write(str(line))
    #~ fw.write("\n")
#~ fw.write("Número deseado de paquetes enviados\n")
#~ for line in DesiredSendPkt:
    #~ fw.write(str(line))
    #~ fw.write("\n")

#~ fw.write("Cálculo realizado con estimación de los paquetes enviados deseados \n Promedio PBR:\n")
#~ for line in MeanPDR2:
    #~ fw.write(str(line))
    #~ fw.write("\n")
#~ fw.write("STD PDR:\n")
#~ for line in  STDPDR2:
    #~ fw.write(str(line))
    #~ fw.write("\n")

fw.close()
