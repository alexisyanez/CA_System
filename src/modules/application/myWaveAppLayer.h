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

#ifndef MODULES_APPLICATION_MYWAVEAPPLAYER_H_
#define MODULES_APPLICATION_MYWAVEAPPLAYER_H_

#include <omnetpp.h>
#include "modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/base/utils/Coord.h"
#include "veins/base/utils/FWMath.h"
//#include "modules/messages/my_WSM_m.h"

#include "modules/messages/WaveShortMessage_m.h"
#include <iostream>
#include <list>


//#include "veins/modules/mac/ieee80211p/Mac1609_4.h"
//#include "modules/mac/MyMac1609_4.h"



using namespace omnetpp;

class myWaveAppLayer : public BaseWaveApplLayer{
    private:
        //Slotted-1-persistant
        bool Slotted1Enabled;
        double Slotted_Ns;
        double Slotted_R;
        double Slotted_tau;

        //TraD
        bool TrADEnabled;
        double TrAD_ti;
        double TrAD_alpha;
        double TrAD_Neig;
        double TrAD_R;

        //DSP
        bool DSPEnabled;

        //Accident
        double Acc_start;
        bool meACC;

        //Periodic WSM
        bool SendP_WSM;
        double WSM_interval;

        //Señal para emitir medida del CBR
        //simsignal_t MyCBRSignal;
        cOutVector MyCBRVec;

        // Vector para almacenar Normalize Times Into Back-Off
        cOutVector NTIB;

        // Vector para almacenar Normalize Broadcast Received
        cOutVector NBR;

        //Señal para emitir medida de MyColl
        //simsignal_t MyCollSignal;
        //cOutVector MyCollVec;

        //Vecinos
        cOutVector Veci;

        //Vecinos segundo salto
        cOutVector Veci2mean;


    public:
        virtual void initialize(int stage);
        virtual void finish();
        double distance(const Coord& a, const Coord& b);

        enum WaveApplMessageKinds {
            CALC_CBR,
            PER_WSM,
            DSP_START
        };

    protected:
        simtime_t lastDroveAt;
        bool sentMessage;
        int currentSubscribedServiceId;

        /* state of the vehicle */
        double angleRad;

        //Coord currposition;
        //Coord currspeed;

        simtime_t lastBusyT;

        // Variables para la implementación de DSP
        simtime_t muDSP;
        double tauDSP;
        bool BT; //Busy tone

        long lastNTIB;
        long currNTIB;

        long lastNBR;
        long currNBR;

        // Promedio de Channel Busy Rate
        //mutable std::list < double > meanCBR;

        //número reportado de vecinos
        mutable std::list < double > NumNeig;

        // Promedio de vecinos de vecinos
        mutable std::list < double > meanNeig2;

        // Promedio de Velocidad
        mutable std::list < double > meanSpeed;


        // Utx Neighbor, función de utilidad para TrAD
        double Utx_n;
        double Dij;

        // último Wsm recibido
        int lastWSMid;

        /* stats */
        //Mide el retardo en la diseminación
        simtime_t delay;
        //Distancia de propagación del mensaje
        double distanceProp;


        //

    protected:
        virtual void onBSM(BasicSafetyMessage* bsm);
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);

        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);

        // Funciones para obtener Utx

        double calculateUtx(simtime_t CBR_n,double Dij_n, int Num_neig_n);
        std::list<std::pair<double,int>> replace(std::list<std::pair<double,int>>mylist,int addressSearch, double UtxReplace);
        bool isNeighbor(std::list<std::pair<double,int>>mylist,int addressSearch);
        int* makePriorList(std::list<std::pair<double,int>>mylist);
        void setingPLinWSM(int* list,WaveShortMessage* wsm);
        int getMyRank(WaveShortMessage* wsm, int my_id);
        double avg(std::list<double> list);


        cMessage* calcCBR_EV;
        cMessage* periodic_WSM_EV;
        cMessage* DSP_start_EV;

        uint32_t generatedWSMsSource;
    };

#endif /* MODULES_APPLICATION_MYWAVEAPPLAYER_H_ */
