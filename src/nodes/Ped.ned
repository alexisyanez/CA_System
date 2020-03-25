package ca_system.nodes;

import org.car2x.veins.base.modules.*;

//import ca_system.modules.nic.Nic80211p;
//import ca_system.modules.nic.INic80211p;

module Ped
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
        appl: ca_system.modules.application.myWaveAppLayer {
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
            
}