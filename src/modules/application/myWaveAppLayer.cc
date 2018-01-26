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

Define_Module(myWaveAppLayer);

void myWaveAppLayer::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);

    Slotted1Enabled = par("Slotted1");
    Slotted_Ns = par("Slotted_Ns");
    Slotted_R = par("Slotted_R");
    Slotted_tau = par("Slotted_tau");

    TrADEnabled = par("TrAD");
    TrAD_ti = par("TrAD_ti");
    TrAD_alpha = par("TrAD_alpha");
    TrAD_Neig = par("TrAD_Neig");
    TrAD_R = par("TrAD_R");

    calcCBR_EV = new cMessage("CBR evt", CALC_CBR);
    lastBusyT = 0;

    if (stage == 0) {
        //Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
//        mymac = FindModule<Mac1609_4*>::findSubModule(getParentModule());
//        assert(mymac);

//        //initialize pointers to other modules
//        if (FindModule<MyMac1609_4*>::findSubModule(getParentModule()))
//        {
//            mymac = MyMacAccess().get(getParentModule());
//        }
//        else {
//            mymac = NULL;
//        }

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
    // Se calcula la distancia y la utilidad del nodo vecino
    Dij = mobility->getPositionAt(SimTime()).distance(bsm->getSenderPos());
    Utx_n=calculateUtx(bsm->getCBR(),Dij,bsm->getNum_Neig());

    // Se agrega a la lista si no esta indexado
    if(!isNeighbor(Neig,bsm->getSenderAddress())){
        std::pair < double, int >p1 = std::make_pair (Utx_n,bsm->getSenderAddress());
        Neig.push_back(p1);
    }
    // si ya está en la lista de vecinos se actualiza su utilidad
    else {
        Neig = replace(Neig,bsm->getSenderAddress(),Utx_n);
    }


}

void myWaveAppLayer::onWSM(WaveShortMessage* wsm) {
    if (My_WSM* mywsm = dynamic_cast<My_WSM*>(wsm)) {
        findHost()->getDisplayString().updateWith("r=16,green");

        //if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getWsmData(), 9999);
        if (!sentMessage) {
            sentMessage = true;
            //repeat the received traffic update once in 2 seconds plus some random delay
            mywsm->setSenderAddress(myId);
            mywsm->setSerial(3);
            if (Slotted1Enabled==true) // Aplicar Retardo según distancia
                {
                // Inicializar variables para calcular el retardo del timeSlot para slotted-1-persistant
                double Sij = Slotted_Ns*(1-(fmin(Dij,Slotted_R)/Slotted_R));
                simtime_t Tslot=Sij*Slotted_tau;
                scheduleAt(simTime() + Tslot , mywsm->dup());
                }
            else if(TrADEnabled==true)
                {
                int rank = getMyRank(mywsm,myId);
                mywsm->setAngleRad(angleRad);
                mywsm->setSenderPos(currposition);
                mywsm->setSenderSpeed(currspeed);
                setingPLinWSM(makePriorList(Neig),mywsm);
                scheduleAt(simTime() + TrAD_ti*rank , mywsm->dup());
                }
            else {
            scheduleAt(simTime() + 2 + uniform(0.01,0.2), mywsm->dup());
            }
        }

    }
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void myWaveAppLayer::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void myWaveAppLayer::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
    case CALC_CBR: {
        currCBR = (mac->getBusyTime()).dbl() - lastBusyT;
        cancelEvent(calcCBR_EV);
        scheduleAt(simTime() + 1, calcCBR_EV);
        EV << "CBR=" << currCBR << endl;
        lastBusyT = (mac->getBusyTime()).dbl();
        break;}
    }

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

//        if (Slotted1Enabled==true) // Aplicar Retardo según distancia
//            {
//            // Inicializar variables para calcular el retardo del timeSlot para slotted-1-persistant
//            double Dij = mobility->getPositionAt(SimTime()).distance(wsm->getSenderPos());// = getDistanceBetweenNodes2(xposition,localLeaderPosition);
//            double Sij = Slotted_Ns*(1-(fmin(Dij,Slotted_R)/Slotted_R));
//            simtime_t Tslot=Sij*Slotted_tau;
//            scheduleAt(simTime() + Tslot , wsm);
//            }
//        else if(TrADEnabled==true)
//            {
//
//            }
//        else {
//            scheduleAt(simTime()+1, wsm);
//        }
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

    angleRad = mobility->getAngleRad();
    currposition = mobility->getCurrentPosition();
    currspeed = mobility->getCurrentSpeed();

    // stopped for for at least 10s?
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
            findHost()->getDisplayString().updateWith("r=16,red");
            sentMessage = true;

            My_WSM* wsm = new My_WSM();

            //WaveShortMessage* wsm = new WaveShortMessage();

            // Seteando valores agreagdos al paquete My_wsm
            wsm->setAngleRad(angleRad);
            wsm->setSenderPos(currposition);
            wsm->setSenderSpeed(currspeed);
            wsm->setOirigin_ID(myId);
            wsm->setOrigin_pos(currposition);
            setingPLinWSM(makePriorList(Neig),wsm);
            wsm->setID(1);

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
    else{
        lastDroveAt = simTime();
    }
}
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class

// Función para descubrir si es ya está indexado como vecino

bool myWaveAppLayer::isNeighbor(std::list<std::pair<double,int>>mylist,int addressSearch){
    std::list < std::pair < double, int >>::iterator it2;
    for (it2 = mylist.begin(); it2 != mylist.end(); it2++) {
        if (it2->second==addressSearch) break;
    }

        if (it2 == mylist.end()) return false;
        else return true;
}

// Función para reemplazar valor de utilidad correspondienteal vecino

std::list<std::pair<double,int>> myWaveAppLayer::replace(std::list<std::pair<double,int>>mylist,int addressSearch, double UtxReplace){
    std::list<std::pair<double,int>> replaceList;
    std::pair < double, int >itp;
    int a;
    double b;
    for (auto it2 = mylist.begin(); it2 != mylist.end(); it2++) {

        if (it2->second == addressSearch) {
            it2->first = UtxReplace;

        }
        b=it2->first;
        a=it2->second;
        itp=std::make_pair (b,a);
        replaceList.push_back(itp);
    }
    return replaceList;
}

double myWaveAppLayer::calculateUtx(double CBR_n,double Dij_n, int Num_neig_n){
    double N=fmin((Num_neig_n/TrAD_Neig),1);
    double D=fmin((Dij_n/TrAD_R),1);
    double W_CBR;
        if(0<CBR_n && CBR_n < 0.6) W_CBR=1;
        else if (0.6<=CBR_n && CBR_n < 0.8) W_CBR=1-CBR_n;
        else if (0.8<=CBR_n && CBR_n < 1) W_CBR=0.001;
    double Utx=W_CBR*(N+D)/2;
    return Utx;
}

int* myWaveAppLayer::makePriorList(std::list<std::pair<double,int>>mylist){
    int* arr = new int[mylist.size()];
    mylist.sort();
    mylist.reverse();
    int i=0;
    for (auto it2 = mylist.begin(); i<mylist.size(); it2++) {
            arr[i]=it2->second;
            i++;
        }
    return arr;

}

void myWaveAppLayer::setingPLinWSM(int* list,My_WSM* wsm){
    for(int i=0;i<sizeof(list);i++){
        wsm->setPriorityList(i,list[i]);
        }
}

int myWaveAppLayer::getMyRank(My_WSM* wsm, int my_id){
    for(int i=0;i<wsm->getPriorityListArraySize();i++){
        if(wsm->getPriorityList(i)==my_id) return i; break;
        }
}

