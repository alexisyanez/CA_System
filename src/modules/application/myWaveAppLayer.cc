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

        // DSP
        DSPEnabled = par("DSP");
        DSP_start_EV = new cMessage("DSP Start", DSP_START);
        tauDSP =par("tauDSP");
        thetaDSP =par("thetaDSP");

        sendBT_EV = new cMessage("BT Event", SEND_BT);
        BT= false;

        StepDSP = 0;
        StepDSP_REC=0;
        LastRTBemID = 0;
        LastWINemID = 0;
        LastACKemID = 0;
        LastWSM_EM= 0;
        MyPartition = -1;
        CW_sug = -1;

        DSP_start_REC_EV = new cMessage("DSP Start Receiver", DSP_START_REC);


        // Accident
        Acc_start = par("Accident_start");
        meACC=par("MeInAcc");

        // Self message para calculcar CBR
        //calcCBR_EV = new cMessage("CBR evt", CALC_CBR);
        //lastBusyT = 0;

        // Inicilizar Numero de veces que entra al backoff
        //lastNTIB = 0;

        // Inicilizar número de broadcast recibidos
        //lastNBR = 0;

       // WSM periódico
        SendP_WSM = par("Send_Per_WSM");
        WSM_interval = par("wsmInterval");
        periodic_WSM_EV = new cMessage("WSM Periodic Transmision evt", PER_WSM);
        generatedWSMsSource= 0;

        // Identificar WSM
        lastWSMid= -1;

        // Setear delay
        delay = -1;

        // Setear distancia de propagación
        distanceProp=-1;

        //
        // MyCollVec.setName("MyColl");
        //MyCBRVec.setName("MyCBR");

        //Número de vecinos

        Veci.setName("Neighbor1-hop");
        Veci2mean.setName("Neighbot2-hop");

        /*lowerLayerIn[0]   = findGate("upperLayerIn",0);
        lowerLayerOut[0] = findGate("upperLayerOut",0);
        lowerControlIn[0]   = findGate("lowerLayerIn",0);
        lowerControlIn[0]  = findGate("lowerLayerOut",0);
        lowerLayerIn[1]   = findGate("upperLayerIn",1);
        lowerLayerOut[1] = findGate("upperLayerOut",1);
        lowerControlIn[1]   = findGate("lowerLayerIn",1);
        lowerControlIn[1]  = findGate("lowerLayerOut",1);*/

    }
    else if (stage == 1) {
        //if(sendWSA){
        //startService(Channels::SCH2, 42, "Traffic Information Service");}
        //Initializing members that require initialized other modules goes here

    }
}

void myWaveAppLayer::finish() {
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

void myWaveAppLayer::onBSM(BasicSafetyMessage* bsm) {
    // Se calcula la distancia y la utilidad del nodo vecino

    Dij = mobility->getPositionAt(SimTime()).distance(bsm->getSenderPos());
    Utx_n=calculateUtx(bsm->getCBR(),Dij,bsm->getNum_Neig());

    //Guardar valor del número de vecinos de cada nodo
    meanNeig2.push_back(bsm->getNum_Neig());

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

void myWaveAppLayer::onWSM(WaveShortMessage* wsm) {

    
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
        else if (DSPEnabled==true)
            {
            MyPartition = getMyPartition(wsm,distanceProp);
            //CW_sug = wsm->getCw();
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

void myWaveAppLayer::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void myWaveAppLayer::onRTB(RTBmessage* rtb) {
    LastRTBemID = rtb->getEm();
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
    if(DSPEnabled==true){
                scheduleAt(simTime(),DSP_start_REC_EV);
                StepDSP_REC=1;
               // Code from paper

    }

}
void myWaveAppLayer::onWIN(WINmessage* win) {
    LastWINemID = win->getEm();
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
    if(DSPEnabled==true){
                scheduleAt(simTime(),DSP_start_REC_EV);
                StepDSP_REC=2;
               // Code from paper
    }
}

void myWaveAppLayer::onACK(ACKmessage* ack) {
    LastACKemID = ack->getEm();
}
void myWaveAppLayer::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
    /*case CALC_CBR: {
        currCBR = mac[0]->getBusyTime() - lastBusyT;
        cancelEvent(calcCBR_EV);
        scheduleAt(simTime() + 1, calcCBR_EV);
        EV << "CBR=" << currCBR << endl;
        lastBusyT = (mac[0]->getBusyTime()).dbl();
        //Emitir estadistica para el CBR
        MyCBRVec.record(currCBR);

        // Guardar valor para el número de veces que entra al Back-off
        currNTIB= mac[0]->getNTIB() - lastNTIB;
        NTIB.record(currNTIB);

        // Guardar valor para el número de broadcast recibidos
        currNBR= mac[0]->getNBR() - lastNBR;
        NBR.record(currNBR);



        //meanCBR.push_back(currCBR);
        //emit(MyCBRSignal,currCBR);
        //Emitir estadistica para el estimador de Colisiones
        //MyCollVec.record(mac->getMyCollisions());
        //emit(MyCollSignal,mac->getMyCollisions());
        break;
    }*/
    case PER_WSM: {

        WaveShortMessage* wsm = new WaveShortMessage();

                    // Seteando valores agreagdos al paquete My_wsm
        wsm->setAngleRad(angleRad);
        wsm->setSenderPos(curPosition);
        wsm->setSenderSpeed(curSpeed);
        wsm->setOirigin_ID(myId);
        wsm->setOrigin_pos(curPosition);

        setingPLinWSM(makePriorList(Neig),wsm);

        generatedWSMsSource++;

        wsm->setID(generatedWSMsSource);
        populateWSM(wsm);
        wsm->setWsmData(mobility->getRoadId().c_str());
        sendDown(wsm,1);

        cancelEvent(periodic_WSM_EV);
        scheduleAt(simTime() + WSM_interval, periodic_WSM_EV);
        EV << "Sending WSM" << endl;
        break;
        }
    case DSP_START:{
        switch(StepDSP){
        case 1:// Step 1 from DSP algorithm
            cancelEvent(DSP_start_EV);
            muDSP = uniform(0,tauDSP); // Step 1
            scheduleAt(simTime()+muDSP,DSP_start_EV); // Step 2
            StepDSP=3;
            break;
        case 3:
            cancelEvent(DSP_start_EV);
            if(LastRTBemID!=1){ // Step 3
                StepDSP=4;
            }
            else{
                StepDSP=0;
                break;
            }

        case 4:
            //Decomentar cuando se arreglen las otras clases
           /* if(mac[0]->getIdleChannel()){ //Step 4
                StepDSP=5;
            }
            else StepDSP=1;*/

        case 5:
            //double myTX;
            StepDSP=51;
            switch (StepDSP){
                case 51:
                    // a) Turn On 2R-BT

                    //Decomentar cuando se arreglen las otras clases
                   /* myTX = mac[0]->getTxPower();
                    mac[0]->setTxPower(myTX*2);*/


                    cancelEvent(sendBT_EV);
                    scheduleAt(simTime(), sendBT_EV);
                    BT=true;
                    StepDSP=52;
                case 52:{

                    // b) Broadcast RTB Packet
                    RTBmessage* rtb = new RTBmessage();
                    rtb->setID(generatedWSMsSource);
                    rtb->setEm(1);
                    populateWSM(rtb);
                    sendDown(rtb,1);
                    StepDSP=53;

                }
                case 53:{
                    // c) Turn Off 2R-BT
                    BT=false;
                    StepDSP=54;
                }
                case 54:
                    // d) Wait for BT activation

                    //Decomentar cuando se arreglen las otras clases
                    //while(mac[0]->getIdleChannel()){
                        EV << "Waiting for BT activation " << endl;
                    }
                    StepDSP=55;
                case 55:// e) Turn On R-BT

                    //Decomentar cuando se arreglen las otras clases
                   /* myTX = mac[0]->getTxPower();
                    mac[0]->setTxPower(myTX/2);*/


                    scheduleAt(simTime(), sendBT_EV);
                    BT=true;
                    StepDSP=56;
                case 56:{
                    // f)Broadcast EM
                    WaveShortMessage* wsm = new WaveShortMessage();
                        // Seteando valores agreagdos al paquete My_wsm
                    wsm->setAngleRad(angleRad);
                    wsm->setSenderPos(curPosition);
                    wsm->setSenderSpeed(curSpeed);
                    wsm->setOirigin_ID(myId);
                    wsm->setOrigin_pos(curPosition);
                    wsm->setCw(2);
                    wsm->setEm(1);
                    setingPLinWSM(makePriorList(Neig),wsm);
                    wsm->setID(1);
                    populateWSM(wsm);
                    wsm->setWsmData(mobility->getRoadId().c_str());
                    //Falta confeccionar el arreglo de particiones!!


                    //host is standing still due to crash
                    if (dataOnSch) {
                        //startService(Channels::SCH2, 42, "Traffic Information Service");
                        //started service and server advertising, schedule message to self to send later
                        scheduleAt(computeAsynchronousSendingTime(1,type_SCH),wsm);
                    }
                    else {
                        //send right away on CCH, because channel switching is disabled
                        sendDown(wsm,1);
                        generatedWSMsSource++;
                        if(SendP_WSM){
                        //cancelEvent(periodic_WSM_EV);
                        scheduleAt(simTime() + WSM_interval, periodic_WSM_EV);}
                    }
                    StepDSP=57;
                }
                case 57:{ // G) Wait For WIN Packet

                    cancelEvent(DSP_start_EV);
                    StepDSP=571;

                    //Decomentar cuando se arreglen las otras clases
                    scheduleAt(simTime()+ DeltaDSP,DSP_start_EV);


                    break;
                }
                case 571:{
                    if (LastWINemID==1){
                            StepDSP=58;
                    }
                    else StepDSP=56;
                }
                case 58:{ //H) Broadcast ACK
                    ACKmessage* ack = new ACKmessage();
                    ack->setID(generatedWSMsSource);
                    ack->setEm(1);
                    populateWSM(ack);
                    sendDown(ack,1);
                    StepDSP=59;
                }
                case 59:{ //I) Turn Off
                    BT=false;
                    break;
                }
              }
            break;
          }
        //}
    case DSP_START_REC:{
            switch(StepDSP_REC){
            case 1:{
                StepDSP_REC = 11;
                switch(StepDSP_REC){
                case 11:{
                    /*myTX = mac[0]->getTxPower();
                    mac[0]->setTxPower(myTX*2);*/
                    cancelEvent(sendBT_EV);
                    scheduleAt(simTime(), sendBT_EV);
                    BT=true;
                    StepDSP_REC=12;
                }
                case 12:
                    while(LastWSM_EM!=1){
                    EV << "Waiting for EM message " << endl;
                    }
                    StepDSP_REC=13;
                case 13:
                    /*Find the Matching partition S, based on its distance to the sender and partition edge inside the EM header   */
                    EV << "My Partition is:" << MyPartition << endl;
                    StepDSP_REC=14;
                case 14:
                    /*Randomly select a contention window from CW_a, and enter the contention phase with a back-off timer. when the timer expires go to next step (e) */

                    StepDSP_REC=15;
                case 15:
                    /*If no WIN packet (with the same EM id) is received, broadcast WIN packet and go to next step (f)*/
                    if(LastWINemID!=1){
                        WINmessage* win = new WINmessage();
                        win->setID(generatedWSMsSource);
                        win->setEm(1);
                        populateWSM(win);
                        sendDown(win,1);
                        StepDSP_REC=16;

                    }
                    else{
                        StepDSP_REC=0;
                        break;
                    }
                case 16:
                    /*Wait for ACK packet from sender. If ACK is received during time \theta, go to next step (g); otherwise, turn off R-BT and stop.*/
                    cancelEvent(DSP_start_REC_EV);
                    scheduleAt(simTime()+ thetaDSP,DSP_start_EV);
                    StepDSP_REC=161;
                    break;
                case 161:
                    if (LastACKemID ==1) StepDSP_REC=17;
                    else{
                        BT=false;
                        break;
                    }
                case 17:{
                    /*Turn off R-BT and Run Sender Procedure*/
                    BT=false;
                    StepDSP=1;
                    scheduleAt(simTime(),DSP_start_EV); // Run sender procedure
                    break;
                }
                }

            }

            case 2:{ // Else if WIN packet is received
                StepDSP_REC = 21;
                switch(StepDSP_REC){
                case 21:
                    /*If the packet has the same EM id with the EM id of the vehicle contention phase,go to next step (b); else do nothing  */
                    if(LastWINemID==1) StepDSP_REC = 22;
                    else break;
                case 22:
                    /*Exit the contention phase; se necesita clarificar mejor la fase de contención*/
                    StepDSP_REC = 23;
                }
            }
            break;
            }
    }
    case SEND_BT: {
        BTmessage* bt = new BTmessage();
        populateWSM(bt);
        sendDown(bt,0);
        cancelEvent(sendBT_EV);
        if (BT){
            //Decomentar cuando se arreglen las otras clases
            scheduleAt(simTime() + BTInterval, sendBT_EV);
        }
        break;
    }
    }

    /*if (WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg)) {
        //send this message on the service channel until the counter is 3 or higher.
        //this code only runs when channel switching is enabled
        sendDown(wsm->dup(),1);
        wsm->setSerial(wsm->getSerial() +1);
        if (wsm->getSerial() >= 3) {
            //stop service advertisements
            stopService();
            delete(wsm);
        }
        else {*/

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
      /*  }
    }
    else {*/
        BaseWaveApplLayer::handleSelfMsg(msg);
    //}


    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission

}

void myWaveAppLayer::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);


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
            wsm->setCw(2);
            wsm->setEm(1);
            setingPLinWSM(makePriorList(Neig),wsm);
            wsm->setID(1);

            if(DSPEnabled == true){
                //muDSP = uniform(0,tauDSP);
                StepDSP=1;
                scheduleAt(simTime(),DSP_start_EV);

            }
            else{
            populateWSM(wsm);
            wsm->setWsmData(mobility->getRoadId().c_str());
            }
            //host is standing still due to crash
            if (dataOnSch) {
                //startService(Channels::SCH2, 42, "Traffic Information Service");
                //started service and server advertising, schedule message to self to send later
                scheduleAt(computeAsynchronousSendingTime(1,type_SCH),wsm);
            }
            else {
                //send right away on CCH, because channel switching is disabled
                sendDown(wsm,1);
                generatedWSMsSource++;
                if(SendP_WSM){
                //cancelEvent(periodic_WSM_EV);
                scheduleAt(simTime() + WSM_interval, periodic_WSM_EV);}
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

bool myWaveAppLayer::isNeighbor(std::list<std::pair<double,int>>mylist,int addressSearch){
    std::list < std::pair < double, int >>::iterator it2;
    for (it2 = mylist.begin(); it2 != mylist.end(); it2++) {
        if (it2->second==addressSearch) break;
    }

        if (it2 == mylist.end()) return false;
        else return true;
}

// Función para reemplazar valor de utilidad correspondiente al vecino

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

double myWaveAppLayer::calculateUtx(simtime_t CBR_r,double Dij_n, int Num_neig_n){
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

int* myWaveAppLayer::makePriorList(std::list<std::pair<double,int>>mylist){
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

void myWaveAppLayer::setingPLinWSM(int* list,WaveShortMessage* wsm){
    wsm->setPriorityListArraySize(sizeof(list));
    for(unsigned int i=0;i<sizeof(list);i++){
        wsm->setPriorityList(i,list[i]);
        }
}

int myWaveAppLayer::getMyRank(WaveShortMessage* wsm, int my_id){
    unsigned int i;
    for(i=0;i<wsm->getPriorityListArraySize();i++){
        if(wsm->getPriorityList(i)==my_id) break;
        }
    return i;
}

double myWaveAppLayer::avg(std::list<double> list)
{
    double avg = 0;
    std::list<double>::const_iterator it3;
    for(it3 = list.begin(); it3 != list.end(); it3++) avg += *it3;
    avg /= list.size();
    return avg;

}

int myWaveAppLayer::getMyPartition(WaveShortMessage* wsm,double Dist){
    //wsm->setPriorityListArraySize(sizeof(list));
    int in=0;
    unsigned int i;
    for(i=0;i < wsm->getPartitionArrayArraySize();i+=2){
        //wsm->setPriorityList(i,list[i]);
        if(wsm->getPartitionArray(i)<Dist && wsm->getPartitionArray(i+1)>Dist){
            in=1;
            break;
        }
        }
    if(in==0){
        EV<<"No está dentro de ninguna partición"<<endl;
        return -1;
    }
    else{
        EV<<"Vehiculo está dentro de la partición"<< i/2 << endl;
        return i/2;
    }
}


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

