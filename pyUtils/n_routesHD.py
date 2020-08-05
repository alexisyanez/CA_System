import sys
import math

out="newroutes"
nameOut = out+".txt" 
fw = open(nameOut, 'w')

#Cars   = 96
#Ped    = 176
#Ciclos = 112
#Total Veh = 208
#Total = 384

#Cars   = 53
#Ped    = 98
#Ciclos = 62
#Total Veh = 115
#Total Nodes = 213
for i in range(0,100,3):
	#r1= ["<person id=\"pedestrian_"+str(i)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152706#1 -152706#2 -152706#3 152701#3 152701#4\" busStop=\"131202\"/>", "<ride busStop=\"131098\" lines=\"5:Larvotto\" intended=\"bus_5:Larvotto.3\" depart=\"150\"/>", "</person>"]
	#r2= ["<person id=\"pedestrian_"+str(i+1)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152780 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	#r3= ["<person id=\"pedestrian_"+str(i+2)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"152701#2 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	r4= ["<person id=\"pedestrian_"+str(i+1)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152701#3 -152706#3 -152706#2 -152706#1\"/>", "</person>"]
	r5= ["<person id=\"pedestrian_"+str(i+2)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152701#3 -152701#2\"/>", "</person>"]
	r6= ["<person id=\"pedestrian_"+str(i+3)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"152701#4 152701#3 152706#3 152706#2 152706#1\"/>", "</person>"]
		
	#~ for j in r1:
		#~ fw.write(j)
		#~ fw.write("\n")
	#~ for j in r2:
		#~ fw.write(j)
		#~ fw.write("\n")
	#~ for j in r3:
		#~ fw.write(j)
		#~ fw.write("\n")
	for j in r4:
		fw.write(j)
		fw.write("\n")
	for j in r5:
		fw.write(j)
		fw.write("\n")
	for j in r6:
		fw.write(j)
		fw.write("\n")
		
for i in range(103,200,3):
	#r1= ["<person id=\"pedestrian_"+str(i)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152706#1 -152706#2 -152706#3 152701#3 152701#4\" busStop=\"131202\"/>", "<ride busStop=\"131098\" lines=\"5:Larvotto\" intended=\"bus_5:Larvotto.3\" depart=\"150\"/>", "</person>"]
	#r2= ["<person id=\"pedestrian_"+str(i+1)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152780 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	#r3= ["<person id=\"pedestrian_"+str(i+2)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"152701#2 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	r4= ["<person id=\"pedestrian_"+str(i+1)+"\" type=\"pedestrian\" depart=\"50\">", "<walk edges=\"-152701#3 -152706#3 -152706#2 -152706#1\"/>", "</person>"]
	r5= ["<person id=\"pedestrian_"+str(i+2)+"\" type=\"pedestrian\" depart=\"50\">", "<walk edges=\"-152701#3 -152701#2\"/>", "</person>"]
	r6= ["<person id=\"pedestrian_"+str(i+3)+"\" type=\"pedestrian\" depart=\"50\">", "<walk edges=\"152701#4 152701#3 152706#3 152706#2 152706#1\"/>", "</person>"]
		
	# for j in r1:
		# fw.write(j)
		# fw.write("\n")
	# for j in r2:
		# fw.write(j)
		# fw.write("\n")
	#for j in r3:
		# fw.write(j)
		# fw.write("\n")
	for j in r4:
		fw.write(j)
		fw.write("\n")
	for j in r5:
		fw.write(j)
		fw.write("\n")
	for j in r6:
		fw.write(j)
		fw.write("\n")

for i in range(203,300,3):
	#r1= ["<person id=\"pedestrian_"+str(i)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152706#1 -152706#2 -152706#3 152701#3 152701#4\" busStop=\"131202\"/>", "<ride busStop=\"131098\" lines=\"5:Larvotto\" intended=\"bus_5:Larvotto.3\" depart=\"150\"/>", "</person>"]
	#r2= ["<person id=\"pedestrian_"+str(i+1)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152780 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	#r3= ["<person id=\"pedestrian_"+str(i+2)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"152701#2 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	r4= ["<person id=\"pedestrian_"+str(i+1)+"\" type=\"pedestrian\" depart=\"100\">", "<walk edges=\"-152701#3 -152706#3 -152706#2 -152706#1\"/>", "</person>"]
	r5= ["<person id=\"pedestrian_"+str(i+2)+"\" type=\"pedestrian\" depart=\"100\">", "<walk edges=\"-152701#3 -152701#2\"/>", "</person>"]
	r6= ["<person id=\"pedestrian_"+str(i+3)+"\" type=\"pedestrian\" depart=\"100\">", "<walk edges=\"152701#4 152701#3 152706#3 152706#2 152706#1\"/>", "</person>"]
		
	# for j in r1:
		# fw.write(j)
		# fw.write("\n")
	# for j in r2:
		# fw.write(j)
		# fw.write("\n")
	# for j in r3:
		# fw.write(j)
		# fw.write("\n")
	for j in r4:
		fw.write(j)
		fw.write("\n")
	for j in r5:
		fw.write(j)
		fw.write("\n")
	for j in r6:
		fw.write(j)
		fw.write("\n")

for i in range(303,400,3):
	#r1= ["<person id=\"pedestrian_"+str(i)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152706#1 -152706#2 -152706#3 152701#3 152701#4\" busStop=\"131202\"/>", "<ride busStop=\"131098\" lines=\"5:Larvotto\" intended=\"bus_5:Larvotto.3\" depart=\"150\"/>", "</person>"]
	#r2= ["<person id=\"pedestrian_"+str(i+1)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"-152780 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	#r3= ["<person id=\"pedestrian_"+str(i+2)+"\" type=\"pedestrian\" depart=\"0\">", "<walk edges=\"152701#2 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	r4= ["<person id=\"pedestrian_"+str(i+1)+"\" type=\"pedestrian\" depart=\"150\">", "<walk edges=\"-152701#3 -152706#3 -152706#2 -152706#1\"/>", "</person>"]
	r5= ["<person id=\"pedestrian_"+str(i+2)+"\" type=\"pedestrian\" depart=\"150\">", "<walk edges=\"-152701#3 -152701#2\"/>", "</person>"]
	r6= ["<person id=\"pedestrian_"+str(i+3)+"\" type=\"pedestrian\" depart=\"150\">", "<walk edges=\"152701#4 152701#3 152706#3 152706#2 152706#1\"/>", "</person>"]
		
	# for j in r1:
		# fw.write(j)
		# fw.write("\n")
	# for j in r2:
		# fw.write(j)
		# fw.write("\n")
	# for j in r3:
		# fw.write(j)
		# fw.write("\n")
	for j in r4:
		fw.write(j)
		fw.write("\n")
	for j in r5:
		fw.write(j)
		fw.write("\n")
	for j in r6:
		fw.write(j)
		fw.write("\n")



for i in range(403,320,6):
	r1= ["<person id=\"pedestrian_"+str(i)+"\" type=\"pedestrian\" depart=\"200\">", "<walk edges=\"-152706#1 -152706#2 -152706#3 152701#3 152701#4\" busStop=\"131202\"/>", "<ride busStop=\"131098\" lines=\"5:Larvotto\" intended=\"bus_5:Larvotto.3\" depart=\"150\"/>", "</person>"]
	r2= ["<person id=\"pedestrian_"+str(i+1)+"\" type=\"pedestrian\" depart=\"200\">", "<walk edges=\"-152780 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	r3= ["<person id=\"pedestrian_"+str(i+2)+"\" type=\"pedestrian\" depart=\"200\">", "<walk edges=\"152701#2 -152701#3\" busStop=\"131098\"/>", "<ride busStop=\"131202\" lines=\"4:Fontvieille\" intended=\"bus_4:Fontvieille.4\" depart=\"150\"/>", "</person>"]
	r4= ["<person id=\"pedestrian_"+str(i+3)+"\" type=\"pedestrian\" depart=\"200\">", "<walk edges=\"-152701#3 -152706#3 -152706#2 -152706#1\"/>", "</person>"]
	r5= ["<person id=\"pedestrian_"+str(i+4)+"\" type=\"pedestrian\" depart=\"200\">", "<walk edges=\"-152701#3 -152701#2\"/>", "</person>"]
	r6= ["<person id=\"pedestrian_"+str(i+5)+"\" type=\"pedestrian\" depart=\"200\">", "<walk edges=\"152701#4 152701#3 152706#3 152706#2 152706#1\"/>", "</person>"]
		
	for j in r1:
		fw.write(j)
		fw.write("\n")
	for j in r2:
		fw.write(j)
		fw.write("\n")
	for j in r3:
		fw.write(j)
		fw.write("\n")
	for j in r4:
		fw.write(j)
		fw.write("\n")
	for j in r5:
		fw.write(j)
		fw.write("\n")
	for j in r6:
		fw.write(j)
		fw.write("\n")		
		

		
fw.close()		
