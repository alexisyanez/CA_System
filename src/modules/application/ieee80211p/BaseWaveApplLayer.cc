//
// Copyright (C) 2011 David Eckhoff <eckhoff@cs.fau.de>
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

#include "modules/application/ieee80211p/BaseWaveApplLayer.h"

const simsignalwrap_t BaseWaveApplLayer::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);
const simsignalwrap_t BaseWaveApplLayer::parkingStateChangedSignal = simsignalwrap_t(TRACI_SIGNAL_PARKING_CHANGE_NAME);

void BaseWaveApplLayer::initialize(int stage) {
    BaseApplLayer::initialize(stage);

    if (stage==0) {

        //initialize pointers to other modules
        if (FindModule<TraCIMobility*>::findSubModule(getParentModule())) {
            mobility = TraCIMobilityAccess().get(getParentModule());
            traci = mobility->getCommandInterface();
            traciVehicle = mobility->getVehicleCommandInterface();
        }
        else {
            traci = NULL;
            mobility = NULL;
            traciVehicle = NULL;
        }

        lowerLayerIn[0]   = findGate("lowerLayerInAP",0);
        lowerLayerOut[0] = findGate("lowerLayerOutAP",0);
        lowerControlIn[0]   = findGate("lowerControlInAP",0);
        lowerControlOut[0]  = findGate("lowerControlOutAP",0);
        lowerLayerIn[1]   = findGate("lowerLayerInAP",1);
        lowerLayerOut[1] = findGate("lowerLayerOutAP",1);
        lowerControlIn[1]   = findGate("lowerControlInAP",1);
        lowerControlIn[1]  = findGate("lowerControlInAP",1);

        annotations = AnnotationManagerAccess().getIfExists();
        ASSERT(annotations);


      //  mac[0] = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(getParentModule());
      //  assert(mac);

        mac[0] = check_and_cast<WaveAppToMac1609_4Interface*>(getModuleByPath("^.nic[0].mac1609_4"));
        //assert(mac[0]);
        mac[1] = check_and_cast<WaveAppToMac1609_4Interface*>(getModuleByPath("^.nic[1].mac1609_4"));
        //assert(mac[1]);


        myId = getParentModule()->getId();


        //read parameters
        headerLength = par("headerLength").longValue();
        sendBeacons = par("sendBeacons").boolValue();
        beaconLengthBits = par("beaconLengthBits").longValue();
        beaconUserPriority = par("beaconUserPriority").longValue();
        beaconInterval =  par("beaconInterval");

        //DSP parameters
        BTInterval = par("BTInterval");
        DeltaDSP = par("DeltaDSP");

        //Start beaconing at time
        beaconAtTime = par("beaconAtTime");

        dataLengthBits = par("dataLengthBits").longValue();
        dataOnSch = par("dataOnSch").boolValue();
        dataUserPriority = par("dataUserPriority").longValue();

        //WSA
        sendWSAs = par("sendWSA").boolValue();
        wsaInterval = par("wsaInterval").doubleValue();
        communicateWhileParked = par("communicateWhileParked").boolValue();
        currentOfferedServiceId = -1;

        isParked = false;


        findHost()->subscribe(mobilityStateChangedSignal, this);
        findHost()->subscribe(parkingStateChangedSignal, this);

        sendBeaconEvt = new cMessage("beacon evt", SEND_BEACON_EVT);
        sendWSAEvt = new cMessage("wsa evt", SEND_WSA_EVT);

        generatedBSMs = 0;
        generatedWSAs = 0;
        generatedWSMs = 0;
        receivedBSMs = 0;
        receivedWSAs = 0;
        receivedWSMs = 0;

    }
    else if (stage == 1) {
        //simulate asynchronous channel access

        if (dataOnSch == true && !mac[1]->isChannelSwitchingActive()) {
            dataOnSch = false;
            std::cerr << "App wants to send data on SCH but MAC doesn't use any SCH. Sending all data on CCH" << std::endl;
        }
        simtime_t firstBeacon = simTime();//beaconAtTime;

        if (par("avoidBeaconSynchronization").boolValue() == true) {

            simtime_t randomOffset = dblrand() * beaconInterval;
            firstBeacon = simTime() + randomOffset; //

            if (mac[1]->isChannelSwitchingActive() == true) {
                if ( beaconInterval.raw() % (mac[1]->getSwitchingInterval().raw()*2)) {
                    std::cerr << "The beacon interval (" << beaconInterval << ") is smaller than or not a multiple of  one synchronization interval (" << 2*mac[1]->getSwitchingInterval() << "). "
                            << "This means that beacons are generated during SCH intervals" << std::endl;
                }
                firstBeacon = computeAsynchronousSendingTime(beaconInterval, type_CCH);
            }
            if(sendWSAs){
                startService(Channels::SCH2, 42, "Traffic Information Service");}

            if (sendBeacons) {
                scheduleAt(firstBeacon, sendBeaconEvt);//beaconAtTime+

            }
        }
    }
}

simtime_t BaseWaveApplLayer::computeAsynchronousSendingTime(simtime_t interval, t_channel chan) {

    /*
     * avoid that periodic messages for one channel type are scheduled in the other channel interval
     * when alternate access is enabled in the MAC
     */

    simtime_t randomOffset = dblrand() * beaconInterval;
    simtime_t firstEvent;
    simtime_t switchingInterval = mac[1]->getSwitchingInterval(); //usually 0.050s
    simtime_t nextCCH;

    /*
     * start event earlierst in next CCH  (or SCH) interval. For alignment, first find the next CCH interval
     * To find out next CCH, go back to start of current interval and add two or one intervals
     * depending on type of current interval
     */

    if (mac[1]->isCurrentChannelCCH()) {
        nextCCH = simTime() - SimTime().setRaw(simTime().raw() % switchingInterval.raw()) + switchingInterval*2;
    }
    else {
        nextCCH = simTime() - SimTime().setRaw(simTime().raw() %switchingInterval.raw()) + switchingInterval;
    }

    firstEvent = nextCCH + randomOffset;

    //check if firstEvent lies within the correct interval and, if not, move to previous interval

    if (firstEvent.raw()  % (2*switchingInterval.raw()) > switchingInterval.raw()) {
        //firstEvent is within a sch interval
        if (chan == type_CCH) firstEvent -= switchingInterval;
    }
    else {
        //firstEvent is within a cch interval, so adjust for SCH messages
        if (chan == type_SCH) firstEvent += switchingInterval;
    }

    return firstEvent;
}

void BaseWaveApplLayer::populateWSM(WaveShortMessage* wsm, int rcvId, int serial) {

    wsm->setWsmVersion(1);
    wsm->setTimestamp(simTime());
    wsm->setSenderAddress(myId);
    wsm->setRecipientAddress(rcvId);
    wsm->setSerial(serial);
    wsm->setBitLength(headerLength);


    if (BasicSafetyMessage* bsm = dynamic_cast<BasicSafetyMessage*>(wsm) ) {
        bsm->setSenderPos(curPosition);
       // bsm->setSenderPos(curPosition);
        bsm->setSenderSpeed(curSpeed);
        bsm->setPsid(-1);
        bsm->setChannelNumber(Channels::CCH);
        bsm->addBitLength(beaconLengthBits);
        bsm->setNum_Neig(Neig.size());
        bsm->setCBR(currCBR);
        bsm->setUserPriority(beaconUserPriority);
    }
    else if (WaveServiceAdvertisment* wsa = dynamic_cast<WaveServiceAdvertisment*>(wsm)) {
        wsa->setChannelNumber(Channels::CCH);
        wsa->setTargetChannel(currentServiceChannel);
        wsa->setPsid(currentOfferedServiceId);
        wsa->setServiceDescription(currentServiceDescription.c_str());
    }
    else if (RTBmessage* rtb = dynamic_cast<RTBmessage*>(wsm) ) {
        rtb->setChannelNumber(Channels::CCH);
       // rtb->setTargetChannel(currentServiceChannel);
        rtb->setPsid(currentOfferedServiceId);
       // rtb->setServiceDescription(currentServiceDescription.c_str());
    }
    else if (WINmessage* win = dynamic_cast<WINmessage*>(wsm) ) {
        win->setChannelNumber(Channels::CCH);
        //win->setTargetChannel(currentServiceChannel);
        win->setPsid(currentOfferedServiceId);
        //win->setServiceDescription(currentServiceDescription.c_str());
    }
    else if (ACKmessage* ack = dynamic_cast<ACKmessage*>(wsm) ) {
        ack->setChannelNumber(Channels::CCH);
        //ack->setTargetChannel(currentServiceChannel);
        ack->setPsid(currentOfferedServiceId);
        //ack->setServiceDescription(currentServiceDescription.c_str());
    }
    else if (BTmessage* bt = dynamic_cast<BTmessage*>(wsm) ) {
            bt->setChannelNumber(Channels::CCH);
            //ack->setTargetChannel(currentServiceChannel);
            bt->setPsid(currentOfferedServiceId);
            //ack->setServiceDescription(currentServiceDescription.c_str());
    }
    else {
        if (dataOnSch) wsm->setChannelNumber(Channels::SCH1); //will be rewritten at Mac1609_4 to actual Service Channel. This is just so no controlInfo is needed
        else wsm->setChannelNumber(Channels::CCH);
        wsm->addBitLength(dataLengthBits);
        wsm->setUserPriority(dataUserPriority);
    }
}

void BaseWaveApplLayer::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal) {
        handlePositionUpdate(obj);
    }
    else if (signalID == parkingStateChangedSignal) {
        handleParkingUpdate(obj);
    }
}

void BaseWaveApplLayer::handlePositionUpdate(cObject* obj) {
    ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
    curPosition = mobility->getCurrentPosition();
    curSpeed = mobility->getCurrentSpeed();
}

void BaseWaveApplLayer::handleParkingUpdate(cObject* obj) {
    //this code should only run when used with TraCI
    isParked = mobility->getParkingState();
    if (communicateWhileParked == false) {
        if (isParked == true) {
            (FindModule<BaseConnectionManager*>::findGlobalModule())->unregisterNic(this->getParentModule()->getSubmodule("nic"));
        }
        else {
            Coord pos = mobility->getCurrentPosition();
            (FindModule<BaseConnectionManager*>::findGlobalModule())->registerNic(this->getParentModule()->getSubmodule("nic"), (ChannelAccess*) this->getParentModule()->getSubmodule("nic")->getSubmodule("phy80211p"), &pos);
        }
    }
}

void BaseWaveApplLayer::handleLowerMsg(cMessage* msg,int index) {

    WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg);
    ASSERT(wsm);

    if (BasicSafetyMessage* bsm = dynamic_cast<BasicSafetyMessage*>(wsm)) {
        receivedBSMs++;
        onBSM(bsm);
    }
    else if (WaveServiceAdvertisment* wsa = dynamic_cast<WaveServiceAdvertisment*>(wsm)) {
        receivedWSAs++;
        onWSA(wsa);
    }
    else if (RTBmessage* rtb = dynamic_cast<RTBmessage*>(wsm)) {
        //receivedWSAs++;
        onRTB(rtb);
    }
    else if (WINmessage* win = dynamic_cast<WINmessage*>(wsm)) {
        //receivedWSAs++;
        onWIN(win);
    }
    else {
        receivedWSMs++;
        onWSM(wsm);
    }

    delete(msg);
}

void BaseWaveApplLayer::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
    case SEND_BEACON_EVT: {
        BasicSafetyMessage* bsm = new BasicSafetyMessage();
        populateWSM(bsm);
        sendDown(bsm,1);
        //int decider = uniform(0,1);
        //if (decider > 0.5){
        //sendDown(bsm,0);}
        //else sendDown(bsm,1);
        cancelEvent(sendBeaconEvt);
        scheduleAt(simTime() + beaconInterval, sendBeaconEvt);
        break;
    }
    case SEND_WSA_EVT:   {
        WaveServiceAdvertisment* wsa = new WaveServiceAdvertisment();
        populateWSM(wsa);
        sendDown(wsa,1);
        cancelEvent(sendWSAEvt);
        scheduleAt(simTime() + wsaInterval, sendWSAEvt);
        break;
    }
    default: {
        if (msg)
            DBG_APP << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
        break;
    }
    }
}

void BaseWaveApplLayer::finish() {
    recordScalar("generatedWSMs",generatedWSMs);
    recordScalar("receivedWSMs",receivedWSMs);

    recordScalar("generatedBSMs",generatedBSMs);
    recordScalar("receivedBSMs",receivedBSMs);

    recordScalar("generatedWSAs",generatedWSAs);
    recordScalar("receivedWSAs",receivedWSAs);
}

BaseWaveApplLayer::~BaseWaveApplLayer() {
    cancelAndDelete(sendBeaconEvt);
    cancelAndDelete(sendWSAEvt);
    findHost()->unsubscribe(mobilityStateChangedSignal, this);
}

void BaseWaveApplLayer::startService(Channels::ChannelNumber channel, int serviceId, std::string serviceDescription) {
    if (sendWSAEvt->isScheduled()) {
        error("Starting service although another service was already started");
    }

    mac[1]->changeServiceChannel(channel);
    currentOfferedServiceId = serviceId;
    currentServiceChannel = channel;
    currentServiceDescription = serviceDescription;

    simtime_t wsaTime = computeAsynchronousSendingTime(wsaInterval, type_CCH); //wsaInterval
    scheduleAt(wsaTime, sendWSAEvt); //+beaconAtTime

}

void BaseWaveApplLayer::stopService() {
    cancelEvent(sendWSAEvt);
    currentOfferedServiceId = -1;
}

void BaseWaveApplLayer::sendDown(cMessage* msg,int index) {
    recordPacket(PassedMessage::OUTGOING,PassedMessage::LOWER_DATA,msg);
    send(msg,lowerLayerOut[index]);
}

//void BaseWaveApplLayer::sendDown(cMessage* msg,int index) {
//    recordPacket(PassedMessage::OUTGOING,PassedMessage::LOWER_DATA,msg);
//    send(msg,lowerLayerOut[index]);
//}

void BaseWaveApplLayer::sendDelayedDown(cMessage* msg, simtime_t delay, int index) {
    checkAndTrackPacket(msg);
    recordPacket(PassedMessage::OUTGOING, PassedMessage::LOWER_DATA, msg);
    sendDelayed(msg, delay, lowerLayerOut[index]);
}

void BaseWaveApplLayer::checkAndTrackPacket(cMessage* msg) {
    if (isParked && !communicateWhileParked) error("Attempted to transmit a message while parked, but this is forbidden by current configuration");

    if (dynamic_cast<BasicSafetyMessage*>(msg)) {
        DBG_APP << "sending down a BSM" << std::endl;
        generatedBSMs++;
    }
    else if (dynamic_cast<WaveServiceAdvertisment*>(msg)) {
        DBG_APP << "sending down a WSA" << std::endl;
        generatedWSAs++;
    }
    else if (dynamic_cast<WaveShortMessage*>(msg)) {
        DBG_APP << "sending down a wsm" << std::endl;
        generatedWSMs++;
    }
}

void BaseWaveApplLayer::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage()){
        handleSelfMsg(msg);
    } else if(msg->getArrivalGateId()==lowerControlIn[0]){
        recordPacket(PassedMessage::INCOMING,PassedMessage::LOWER_CONTROL,msg);
        handleLowerControl(msg);
    } else if(msg->getArrivalGateId()==lowerLayerIn[0]){
        recordPacket(PassedMessage::INCOMING,PassedMessage::LOWER_DATA,msg);
        handleLowerMsg(msg,0);
    } else if(msg->getArrivalGateId()==lowerControlIn[1]){
        recordPacket(PassedMessage::INCOMING,PassedMessage::LOWER_CONTROL,msg);
        handleLowerControl(msg);
    } else if(msg->getArrivalGateId()==lowerLayerIn[1]){
        recordPacket(PassedMessage::INCOMING,PassedMessage::LOWER_DATA,msg);
        handleLowerMsg(msg,1);
    }
    else if(msg->getArrivalGateId()==-1) {
        /* Classes extending this class may not use all the gates, f.e.
         * BaseApplLayer has no upper gates. In this case all upper gate-
         * handles are initialized to -1. When getArrivalGateId() equals -1,
         * it would be wrong to forward the message to one of these gates,
         * as they actually don't exist, so raise an error instead.
         */
        throw cRuntimeError("No self message and no gateID?? Check configuration.");
    } else {
        /* msg->getArrivalGateId() should be valid, but it isn't recognized
         * here. This could signal the case that this class is extended
         * with extra gates, but handleMessage() isn't overridden to
         * check for the new gate(s).
         */
        throw cRuntimeError("Unknown gateID?? Check configuration or override handleMessage().");
    }
}

void BaseWaveApplLayer::sendControlDown(cMessage *msg, int index) {
    recordPacket(PassedMessage::OUTGOING,PassedMessage::LOWER_CONTROL,msg);
    if (gate(lowerControlOut[index])->isPathOK())
        send(msg, lowerControlOut[index]);
    else {
        EV << "BaseLayer: lowerControlOut is not connected; dropping message" << std::endl;
        delete msg;
    }
}
