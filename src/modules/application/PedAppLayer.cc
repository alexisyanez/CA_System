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

#include "PedAppLayer.h"


Define_Module(PedAppLayer);

void PedAppLayer::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);

    //currentPosXVec.setName("posx");



    if (stage == 0) {
        //Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;

        // Parametros para Slotted
        Slotted1Enabled = par("Slotted1");
        Slotted_Ns = par("Slotted_Ns");
        Slotted_R = par("Slotted_R");
        Slotted_tau = par("Slotted_tau");

        // Parametros pas TrAD
        TrADEnabled = par("TrAD");
        TrAD_ti = par("TrAD_ti");
        TrAD_alpha = par("TrAD_alpha");
        TrAD_Neig = par("TrAD_Neig");
        TrAD_R = par("TrAD_R");

        

        // Accident
        Acc_start = par("Accident_start");
        meACC=par("MeInAcc");

        //MovinPed
        MovinPed = par("MovinPed");

        //Multiple Tx Rates
        MultipleTx = par("MultipleTx");

        //On-StreetPed
        OnStreet = par("OnStreet");

//        // Self message para calculcar CBR
//        calcCBR_EV = new cMessage("CBR evt", CALC_CBR);
//
//        lastBusyT = 0;
//
//        // Inicilizar Numero de veces que entra al backoff
//        lastNTIB = 0;
//        currNTIB = 0;
//
//        // Inicilizar número de broadcast recibidos
//        lastNBR = 0;
//        currNBR = 0;

       // WSM periódico
        SendP_WSM = par("Send_Per_WSM");
        WSM_interval = par("wsmInterval");
        //periodic_WSM_EV = new cMessage("WSM Periodic Transmision evt", PER_WSM);

        generatedWSMsSource= 0;

        // Identificar WSM
        lastWSMid= -1;

        // Setear delay
        delay = -1;

        // Setear distancia de propagación
        distanceProp=-1;

        //
        // MyCollVec.setName("MyColl");
//        MyCBRVec.setName("MyCBR");
//        NTIB.setName("NTIB");
//        NBR.setName("NBR");
//
//        //Número de vecinos
//
        Veci.setName("Neighbor1-hop");
        Veci2mean.setName("Neighbot2-hop");
//
//        CBR_Int= par("CBRInterval");



    }
    else if (stage == 1) {
        //if(sendWSA){
        //startService(Channels::SCH2, 42, "Traffic Information Service");}
        //Initializing members that require initialized other modules goes here
        //cancelEvent(calcCBR_EV);
        //scheduleAt(simTime() + CBR_Int, calcCBR_EV);

    }
}

void PedAppLayer::finish() {
    //statistics recording goes here
    BaseWaveApplLayer::finish();
    recordScalar("delayWSM",delay.dbl());
    recordScalar("Dist_Propa",distanceProp);
    //recordScalar("Mean_CBR",avg(meanCBR));
    recordScalar("Mean_Speed",avg(meanSpeed));
    /*NumNeig.pop_front();
    recordScalar("Mean_Neig",avg(NumNeig));
    recordScalar("Mean_Neig_of_Neig",avg(meanNeig2));*/


}

void PedAppLayer::onBSM(BasicSafetyMessage* bsm) {
    // Se calcula la distancia y la utilidad del nodo vecino

    Dij = mobility->getPositionAt(SimTime()).distance(bsm->getSenderPos());
    // Utx_n=calculateUtx(bsm->getCBR(),Dij,bsm->getNum_Neig());

    //Guardar valor del número de vecinos de cada nodo
    //meanNeig2.push_back(bsm->getNum_Neig());

    // Se agrega a la lista si no está indexado
    if(!isNeighbor(Neig,bsm->getSenderAddress())){
        std::pair < double, int >p1 = std::make_pair (Utx_n,bsm->getSenderAddress());
        Neig.push_back(p1);
    }
    // Si ya está en la lista de vecinos se actualiza su utilidad
    else {
        Neig = replace(Neig,bsm->getSenderAddress(),Utx_n);
        // Guardar valor de vecinos 1 y 2 saltos
        Veci.record(Neig.size());
        Veci2mean.record(avg(meanNeig2));
    }


}

void PedAppLayer::onWSM(WaveShortMessage* wsm) {
    
    //LastWSM_EM=wsm->getEm();
    if (wsm->getID()!=lastWSMid && wsm->getOirigin_ID()!=myId ){
    findHost()->getDisplayString().updateWith("r=16,green");
    EV << "I am green because onWSM function was activated" << endl;

    delay=simTime()-wsm->getTimestamp();
    distanceProp = mobility->getPositionAt(SimTime()).distance(wsm->getSenderPos()); //Dij;
   // wsm->setCw(2);
   // wsm->setEm(1);
    //if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getWsmData(), 9999);
    if (!sentMessage) {
        sentMessage = true;
        //repeat the received traffic update once in 2 seconds plus some random delay
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        if (Slotted1Enabled==true) // Aplicar Retardo según distancia
            {
            if(Enable_aware==true){
                Slotted_Ns=Ns_sug;
            }

            // Inicializar variables para calcular el retardo del timeSlot para slotted-1-persistant
            double Sij = Slotted_Ns*(1-(fmin(Dij,Slotted_R)/Slotted_R));
            simtime_t Tslot=Sij*Slotted_tau;
            scheduleAt(simTime() + Tslot , wsm->dup());
            }
        else if(TrADEnabled==true)
            {
            int rank = getMyRank(wsm,myId);
            wsm->setAngleRad(angleRad);
            wsm->setSenderPos(curPosition);
            wsm->setSenderSpeed(curSpeed);
            setingPLinWSM(makePriorList(Neig),wsm);
            simtime_t TS =  TrAD_ti*rank;
            scheduleAt(simTime() + TS , wsm->dup());
            }
        else {
        scheduleAt(simTime() + 2 + uniform(0.01,0.2), wsm->dup());
        }
        lastWSMid=1;
    }
    }
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void PedAppLayer::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void PedAppLayer::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
        case SEND_BEACON_EVT: {

            EV << "My current Speed= " << curSpeed << endl;
            EV << "My current Edge= " << curEdge << endl;
            double mySpeed =sqrt(pow((curSpeed.x),2)+pow((curSpeed.y),2));

            EV << "My boolean OnStreet is= " << OnStreet << endl;
            EV << "My boolean MovinPed is= " << MovinPed << endl;
            EV << "My boolean MultipleTx is= " << MultipleTx  << endl;

            EV << "My absolute current Speed Calculated= " << mySpeed << endl;
            // EV << "My current Edge= " << curEdge << endl;

            if ( std::isnan(mySpeed) == 1 ){
                mySpeed =1;
            }


            if ( OnStreet && curEdge.find("w")){
                BasicSafetyMessage* bsm = new BasicSafetyMessage();
                populateWSM(bsm);
                sendDown(bsm);
                EV << "I'm On Street, so i will transmit "<< endl;
            }
            else if ( OnStreet && !curEdge.find("w")){
                beaconInterval = 1;
                EV << "I'm not On Street, so i won't transmit "<< endl;
            }

            if ( MovinPed && mySpeed > 0){
                BasicSafetyMessage* bsm = new BasicSafetyMessage();
                populateWSM(bsm);
                sendDown(bsm);
                EV << "I'm Moving, so i will transmit "<< endl;
            }
            else if ( MovinPed && mySpeed == 0){
                beaconInterval = 1;
                EV << "I'm not Moving, so i won't transmit "<< endl;
            }

            if ( MultipleTx && mySpeed > 0){
                BasicSafetyMessage* bsm = new BasicSafetyMessage();
                populateWSM(bsm);
                sendDown(bsm);
                beaconInterval = 0.2;
                EV << "I'm moving, so i will transmit with multiple Tx "<< endl;
            }
            else if ( MultipleTx && mySpeed == 0){
                BasicSafetyMessage* bsm = new BasicSafetyMessage();
                populateWSM(bsm);
                sendDown(bsm);
                beaconInterval = 0.5;
                EV << "I'm moving, so i will transmit with multiple Tx "<< endl;
            }
            if (!OnStreet && !MultipleTx && !MovinPed){
                BasicSafetyMessage* bsm = new BasicSafetyMessage();
                populateWSM(bsm);
                sendDown(bsm);
                EV << "No have rules, so transmit with Beacon-interval "<< endl;
            }

            cancelEvent(sendBeaconEvt);
            scheduleAt(simTime() + beaconInterval, sendBeaconEvt);
            break;

            }
        case SEND_WSA_EVT:   {
            WaveServiceAdvertisment* wsa = new WaveServiceAdvertisment();
            populateWSM(wsa);
            sendDown(wsa);
            cancelEvent(sendWSAEvt);
            scheduleAt(simTime() + wsaInterval, sendWSAEvt);
            break;
        }
        case CALC_CBR: {
            currCBR = mac->getBusyTime() - lastBusyT;
            cancelEvent(calcCBR_EV);
            scheduleAt(simTime() + CBR_Int, calcCBR_EV);
            EV << "CBR=" << currCBR << endl;
            lastBusyT = (mac->getBusyTime()).dbl();
            //Emitir estadistica para el CBR
            MyCBRVec.record(currCBR);

            // Guardar valor para el número de veces que entra al Back-off
            currNTIB= mac->getNTIB() - lastNTIB;
            NTIB.record(currNTIB);
            EV << "Normalize Time Into BackOff NTIB= " << currNTIB << endl;


            // Guardar valor para el número de broadcast recibidos
            currNBR= mac->getNBR() - lastNBR;
            NBR.record(currNBR);
            EV << "Normalize Broadcast Received NBR=" << currNBR << endl;
    //        EV << "Se envian métricas para la clasificación del contexto, Descriptor: " << getDescriptor(currCBR.dbl(),currNTIB,currNBR) << endl;

            lastNBR = mac->getNBR();
            lastNTIB = mac->getNTIB();
            lastBusyT = mac->getBusyTime();

            if (Enable_aware == true){
                int Predict_NTL = getDescriptor(currCBR.dbl(),(double)currNTIB,(double)currNBR,(double)Neig.size());
                EV << "Descriptor: " << Predict_NTL << endl;

                // Gaurdar valores de aciertos en la clasificación
                if (Predict_NTL == NTL_tar){
                    // the classification was success
                    hit.push_back(1);
                }
                else{
                    // the classification was wrong
                    hit.push_back(0);
                }

                // Entregar valor sugerido para Ns

                if (Neig.size() < 80){
                    Ns_sug=2;
                }
                else if (Neig.size() >= 80 && Predict_NTL == 2){
                    Ns_sug=5;
                }
                else if (Neig.size() >= 80 && (Predict_NTL == 0 || Predict_NTL == 1 )){
                    Ns_sug=7;
                }
            }

            break;

        }
        default: {
            if (msg)
                DBG_APP << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
        }


}

void PedAppLayer::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    curEdge = mobility->getRoadId();
    angleRad = mobility->getAngleRad();
    //currposition = mobility->getCurrentPosition();
    //currspeed = mobility->getCurrentSpeed();
    meanSpeed.push_back(sqrt(pow((curSpeed.x),2)+pow((curSpeed.y),2)));
    NumNeig.push_back(Neig.size());

    // stopped for at least 10s?
    // if (mobility->getSpeed() < 1) {
    // Accidente programado
    if (meACC &&  Acc_start < simTime().dbl() && sentMessage == false ){
       // if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
            findHost()->getDisplayString().updateWith("r=16,red");
            sentMessage = true;

            // Cofirmar que es quien genera WSM
            delay = -2;

            //My_WSM* wsm = new My_WSM();
            WaveShortMessage* wsm = new WaveShortMessage();

            // Seteando valores agreagdos al paquete My_wsm
            wsm->setAngleRad(angleRad);
            wsm->setSenderPos(curPosition);
            wsm->setSenderSpeed(curSpeed);
            wsm->setOirigin_ID(myId);
            wsm->setOrigin_pos(curPosition);

            setingPLinWSM(makePriorList(Neig),wsm);
            wsm->setID(1);

            wsm->setID(1);

            populateWSM(wsm);
            wsm->setWsmData(mobility->getRoadId().c_str());

            //host is standing still due to crash
            if (dataOnSch) {
                //startService(Channels::SCH2, 42, "Traffic Information Service");
                //started service and server advertising, schedule message to self to send later
                scheduleAt(computeAsynchronousSendingTime(1,type_SCH),wsm);
            }
            else {
                //send right away on CCH, because channel switching is disabled
                sendDown(wsm);
                generatedWSMsSource++;
                //if(SendP_WSM){
                //cancelEvent(periodic_WSM_EV);
                //scheduleAt(simTime() + WSM_interval, periodic_WSM_EV);}
            }
        //}
    }
    else{
        lastDroveAt = simTime();
    }
}
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class

// Función para descubrir si es ya está indexado como vecino

bool PedAppLayer::isNeighbor(std::list<std::pair<double,int>>mylist,int addressSearch){
    std::list < std::pair < double, int >>::iterator it2;
    for (it2 = mylist.begin(); it2 != mylist.end(); it2++) {
        if (it2->second==addressSearch) break;
    }

        if (it2 == mylist.end()) return false;
        else return true;
}

// Función para reemplazar valor de utilidad correspondiente al vecino

std::list<std::pair<double,int>> PedAppLayer::replace(std::list<std::pair<double,int>>mylist,int addressSearch, double UtxReplace){
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

double PedAppLayer::calculateUtx(simtime_t CBR_r,double Dij_n, int Num_neig_n){
    double CBR_n = CBR_r.dbl();
    double N=fmin((Num_neig_n/TrAD_Neig),1);
    double D=fmin((Dij_n/TrAD_R),1);
    double W_CBR;
        if(0<CBR_n && CBR_n < 0.6) W_CBR=1;
        else if (0.6<=CBR_n && CBR_n < 0.8) W_CBR=1-CBR_n;
        else if (0.8<=CBR_n && CBR_n < 1) W_CBR=0.001;
    double Utx=W_CBR*(N+D)/2;
    return Utx;
}

int* PedAppLayer::makePriorList(std::list<std::pair<double,int>>mylist){
    int* arr = new int[mylist.size()];
    mylist.sort();
    mylist.reverse();
    unsigned int i=0;
    for (auto it2 = mylist.begin(); i<mylist.size(); it2++) {
            arr[i]=it2->second;
            i++;
        }
    return arr;

}

void PedAppLayer::setingPLinWSM(int* list,WaveShortMessage* wsm){
    wsm->setPriorityListArraySize(sizeof(list));
    for(unsigned int i=0;i<sizeof(list);i++){
        wsm->setPriorityList(i,list[i]);
        }
}

int PedAppLayer::getMyRank(WaveShortMessage* wsm, int my_id){
    unsigned int i;
    for(i=0;i<wsm->getPriorityListArraySize();i++){
        if(wsm->getPriorityList(i)==my_id) break;
        }
    return i;
}

//double myWaveAppLayer::avg(std::list<double> list)
//{
//    double avg = 0;
//    std::list<double>::const_iterator it3;
//    for(it3 = list.begin(); it3 != list.end(); it3++) avg += *it3;
//    avg /= list.size();
//    return avg;
//
//}


//
//int myWaveAppLayer::getDescriptor(double CBR,double NTIB, double NBR){
//    int Desc;
//    char cmd[110];
//    sprintf(cmd,"%s %f %f %f","python /home/alexis/git/CA_System/pyUtils/client.py",CBR,NTIB,NBR);
//    EV << "******* " << cmd << std::endl;
//    pyin = popen(cmd, "r");
//    fscanf(pyin, "%i", &Desc);
//    pclose(pyin);
//    return Desc;
//
//}

