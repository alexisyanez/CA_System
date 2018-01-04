//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "myWaveAppLayer.h"
//#include <cmath>


Define_Module(myWaveAppLayer);

void myWaveAppLayer::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);

    Slotted1Enabled = par("Slotted1");
    Slotted_Ns = par("Slotted_Ns");
    Slotted_R = par("Slotted_R");
    Slotted_tau = par("Slotted_tau");

    if (stage == 0) {
        //Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }
    else if (stage == 1) {
        //Initializing members that require initialized other modules goes here

    }
}

void myWaveAppLayer::finish() {
    BaseWaveApplLayer::finish();
    //statistics recording goes here

}

void myWaveAppLayer::onBSM(BasicSafetyMessage* bsm) {
    //Your application has received a beacon message from another car or RSU
    //code for handling the message goes here

}

void myWaveAppLayer::onWSM(WaveShortMessage* wsm) {
    findHost()->getDisplayString().updateWith("r=16,green");

    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getWsmData(), 9999);
    if (!sentMessage) {
        sentMessage = true;
        //repeat the received traffic update once in 2 seconds plus some random delay
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        scheduleAt(simTime() + 2 + uniform(0.01,0.2), wsm->dup());
    }


    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void myWaveAppLayer::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void myWaveAppLayer::handleSelfMsg(cMessage* msg) {
    if (My_WSM* wsm = dynamic_cast<My_WSM*>(msg)) {
        //send this message on the service channel until the counter is 3 or higher.
        //this code only runs when channel switching is enabled
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() +1);
        if (wsm->getSerial() >= 3) {
            //stop service advertisements
            stopService();
            delete(wsm);
        }
        else {


        // Inicializar variables para calcular el retardo del timeSlot para slotted-1-persistant

       // double Ns= 5;
       // double R = 40;

        double Dij = mobility->getPositionAt(SimTime()).distance(wsm->getSenderPos());// = getDistanceBetweenNodes2(xposition,localLeaderPosition);
        double Sij = Slotted_Ns*(1-(fmin(Dij,Slotted_R)/Slotted_R));
        simtime_t Tslot=Sij*Slotted_tau;

        if (Slotted1Enabled==true) // Aplicar Retardo según distancia
                        {
                            scheduleAt(simTime() + Tslot , wsm);
                        }
        else {
            scheduleAt(simTime()+1, wsm);
        }
        }
    }
    else {
        BaseWaveApplLayer::handleSelfMsg(msg);
    }


    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission

}

void myWaveAppLayer::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    // stopped for for at least 10s?
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
            findHost()->getDisplayString().updateWith("r=16,red");
            sentMessage = true;

            WaveShortMessage* wsm = new WaveShortMessage();
            populateWSM(wsm);
            wsm->setWsmData(mobility->getRoadId().c_str());

            //host is standing still due to crash
            if (dataOnSch) {
                startService(Channels::SCH2, 42, "Traffic Information Service");
                //started service and server advertising, schedule message to self to send later
                scheduleAt(computeAsynchronousSendingTime(1,type_SCH),wsm);
            }
            else {
                //send right away on CCH, because channel switching is disabled
                sendDown(wsm);
            }
        }
    }
    else {
        lastDroveAt = simTime();
    }
}
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class

