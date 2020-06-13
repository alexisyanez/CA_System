//
// Copyright (C) 2008 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

package ca_system.nodes;

import org.car2x.veins.base.modules.*;

import ca_system.base.modules.*;
//import ca_system.modules.nic.INic80211p;

module Car
{
    parameters:
        string applType; //type of the application layer
        string nicType = default("ca_system.modules.nic.Nic80211p"); // type of network interface card
        //string nicType2 = default("Nic80211p2"); // type of network interface card for DPS
        string veinsmobilityType = default("org.car2x.veins.modules.mobility.traci.TraCIMobility"); //type of the mobility module
        //int numRadios = default(2);

        //Señal para guardar CBR
        @signal[MyCBR](type="double");
        @statistic[MyCBR](title="Calculo de Channel Busy Ratio"; source="MyCBR"; record=vector,stats; interpolationmode=none);

		//Señal para guardar My Collisions
        @signal[MyCollisions](type="long");
        @statistic[MyCollisions](title="Collision estimator from backoff"; source="MyColl"; record=vector,stats; interpolationmode=none);
        @display("bgb=307,273");
    gates:
        input veinsradioIn @directIn; // gate for sendDirect
        //input veinsradioIn2 @directIn; 
        //input veinsradioIn2; // gate for DPS
    submodules:
        appl: <applType> like org.car2x.veins.base.modules.IBaseApplLayer{ //ca_system.modules.application.myWaveAppLayer {
            parameters:
                @display("p=60,50");
            gates:
                lowerLayerIn; // from network layer
                lowerLayerOut; // to network layer
                lowerControlIn; // control from network layer
                lowerControlOut; // control to network layerlowerControlIn[numRadios]; // control from network layer
        }

        nic: ca_system.modules.nic.Nic80211p {
            parameters:
                @display("p=60,166");
        }

        //       	nic2: <nicType2> like ca_system.modules.nic.INic80211p2 {
        //           	parameters:
        //                @display("p=153,50");
        //        }
        veinsmobility: <veinsmobilityType> like org.car2x.veins.base.modules.IMobility {
            parameters:
                @display("p=191,166;i=block/cogwheel");
        }

    connections allowunconnected:

        //for i=0..numRadios-1 {
            nic.upperLayerOut --> appl.lowerLayerIn;
            nic.upperLayerIn <-- appl.lowerLayerOut;
            nic.upperControlOut --> appl.lowerControlIn;
            nic.upperControlIn <-- appl.lowerControlOut;

            veinsradioIn --> nic.radioIn;
            
           // nic[1].upperLayerOut --> appl.lowerLayerInAP[1];
           // nic[1].upperLayerIn <-- appl.lowerLayerOutAP[1];
           // nic[1].upperControlOut --> appl.lowerControlInAP[1];
           // nic[1].upperControlIn <-- appl.lowerControlOutAP[1];

          //  veinsradioIn2 --> nic[1].radioIn; // Fot the use of SendDirect is necessary to separte radio, 
            								  //the vector gate for veinsRadioin not recognized diferents gates 
        //}

//       	nic2.upperLayerOut2 --> appl.lowerLayerIn2;
//       	nic2.upperLayerIn2 <-- appl.lowerLayerOut2;
//       	nic2.upperControlOut2 --> appl.lowerControlIn2;
//       	nic2.upperControlIn2 <-- appl.lowerControlOut2;
//
//        	veinsradioIn2 --> nic2.radioIn2;
        //}

}
