#!/usr/bin/env python
"""
@file    runner.py
@author  Lena Kalleske
@author  Daniel Krajzewicz
@author  Michael Behrisch
@date    2009-03-26
@version $Id: runner.py 14678 2013-09-11 08:53:06Z behrisch $

Route generation script.

SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
Copyright (C) 2009-2012 DLR/TS, Germany

This file is part of SUMO.
SUMO is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.
"""

import os, sys
import optparse
import subprocess
import random

def generate_routefile():
    random.seed(41) # make tests reproducible
    N = 2000 # number of time steps
    Nr = 25	
    # demand per second from different directions
    pBus = 1./4 		#right-down road
    #pLL = 1./11			#Left-left road
    #pDL = 1./12			#Down-low road
    #pDR = 1./30			#Down-right road
    #pDD = 1./1			#Down-down road
    with open("cross.rou.xml", "w") as routes:
        print >> routes, """<?xml version="1.0"?>
<routes>
   <vType id="typePassenger" accel="2.6" decel="4.5" sigma="0.5" length="2.5" minGap="1" maxSpeed="19" guiShape="passenger"/>
   <vType id="typeBus" accel="0.8" decel="4.5" sigma="0.5" length="10" minGap="3" maxSpeed="19" guiShape="bus" vClass="bus"/>

   <route id="route0" edges="446594494#0 7981319#0 151097617#0 151097617#1 447281176 38619574 447281177#0 447281177#1 447281177#2 447281177#3"/>

   <route id="route1" edges="223300795#0 223300795#4 223300795#5 223300795#6 121815695#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 23321634 447281177#0 447281177#1 447281177#2 23321901 20891194#2 20891194#3"/>

   <route id="route2" edges="223300795#0 223300795#4 223300795#5 223300795#6 121815695#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 23321634 447281177#0 447281177#1 447281177#2 23321901 20891194#2 20891194#3"/>

   <route id="route3" edges="223300795#0 223300795#4 223300795#5 23321898#0 23321897#2 23321897#3 449284320#1 20891186#0 -20891194#0"/>

   <route id="route4" edges="11490172#0 11490172#2 39334084 448533599#0 448533599#1 448533599#2 448533599#3 448533599#4 448736027#3 223300795#5 223300795#6 121815695#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 121815695#3 121815695#4"/>

   <route id="route5" edges="23321897#0 23321897#1 23321897#2 23321897#3 449284320#1 449284320#2 449284320#3 121815661#0 121815661#1"/>
    
   <route id="route6" edges="448736027#0 448736027#2 448736027#3 223300795#5 223300795#6 121815695#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 121815695#3 121815695#4"/>

   <route id="route7" edges="23321897#0 23321897#1 23321897#2 23321897#3 449284320#1 449284320#2 449284320#3 121815661#0 448533599#1 448533599#2 448533599#3 448533599#4 448533599#5"/>

   <route id="route8" edges="11490172#0 11490172#2 39334084 448533599#0 448533599#1 448533599#2 448533599#3 448533599#4 448736027#3 407593363#0 407593363#1"/>
    
   <route id="route9" edges="223300795#0 223300795#4 223300795#5 223300795#6 121815695#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 23321634 447281177#0 447281177#1 20891186#2"/>
   
   <route id="route10" edges="449284320#0 449284320#1 449284320#2 41078120#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 121815695#3 121815695#4"/>

   <route id="route11" edges="23321920 23321897#1 23321897#2 23321897#3 449284320#1 449284320#2 41078120#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 23321634 447281177#0 20891191"/>
 
   <route id="route12" edges="11490172#0 11490172#2 39334084 448533599#0 448533599#1 448533599#2 448533599#3 448533599#4 448736027#3 223300795#5 23321898#0 23321898#2"/>
    
   <route id="route13" edges="23321897#0 23321897#1 23321897#2 23321897#3 449284320#1 20891186#0 -20891194#0"/>

   <route id="route14" edges="223300795#0 223300795#4 223300795#5 223300795#6 121815695#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 23321634 447281177#0 447281177#1 20891186#2"/>
    
   <route id="route15" edges="223300795#0 223300795#4 223300795#5 223300795#6 121815661#0 448533599#1 448533599#2 448533599#3 448533599#4 448533599#5"/>

   <route id="route16" edges="23321897#0 23321897#1 23321897#2 23321897#3 449284320#1 449284320#2 41078120#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 121815695#3 121815695#4"/>

   <route id="route17" edges="449284320#0 449284320#1 449284320#2 41078120#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 121815695#3 121815695#4"/>

   <route id="route18" edges="449284320#0 449284320#1 449284320#2 449284320#3 121815662#0 121815662#1 121815662#2 407593363#0 407593363#1"/>

   <route id="route19" edges="223300795#0 223300795#4 223300795#5 223300795#6 121815695#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 23321634 447281177#0 72839412"/>
      
   <route id="route20" edges="223300795#0 223300795#4 223300795#5 223300795#6 121815695#0 121815695#1 121815695#2-AddedOnRampEdge 121815695#2 121815695#3 121815695#4"/>
   
   <route id="route21" edges="446594494#0 446594494#2 121815662#0 121815662#1 121815662#2 407593363#0 407593363#1"/>

   <route id="route22" edges="449284320#0 449284320#1 449284320#2 449284320#3 121815661#0 121815661#1"/>

   <route id="route23" edges="11490172#0 11490172#2 447281176 38619574 447281177#0 447281177#1 447281177#2 447281177#3"/>

   <route id="route24" edges="448736027#0 448736027#2 448736027#3 223300795#5 23321898#0 23321898#2"/>"""
        lastVeh = 0
        vehNr = 0
	countNr = 0 
        for i in range(N):
            if random.uniform(0,1) < pBus:
                print >> routes, '    <vehicle id="%i" type="typeBus" route="route%i" depart="%i" departPos="random_free"/>' % (i,countNr,random.randrange(5))
                vehNr += 1
                lastVeh = i
            else: 
                print >> routes, '    <vehicle id="%i" type="typePassenger" route="route%i" depart="%i" departPos="random_free"/>' % (i,countNr,random.randrange(5))
                vehNr += 1
                lastVeh = i
	    if countNr == Nr-1: countNr=0	
            else: countNr+= 1
	
	for i in range(Nr):
 	    if i > 19:	
            	if random.uniform(0,1) < pBus:
			print >> routes, '    <flow id="flow%s" type="typeBus" route="route%s" begin="0" period="1" number="195"/>' % (i,i)	
    	    	else: 
			print >> routes, '    <flow id="flow%s" type="typePassenger" route="route%s" begin="0" period="1" number="195"/>' % (i,i)
	    else:
		if random.uniform(0,1) < pBus:
			print >> routes, '    <flow id="flow%s" type="typeBus" route="route%s" begin="0" period="3" number="195"/>' % (i,i)	
    	    	else: 
			print >> routes, '    <flow id="flow%s" type="typePassenger" route="route%s" begin="0" period="3" number="195"/>' % (i,i)	
        print >> routes, "</routes>"

# this is the main entry point of this script
if __name__ == "__main__":
    
    generate_routefile()
