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

        //Accident
        double Acc_start;
        bool meACC;

        //Periodic WSM
        bool SendP_WSM;
        double WSM_interval;

        //Señal para emitir medida del CBR
        //simsignal_t MyCBRSignal;
        cOutVector MyCBRVec;

        //Señal para emitir medida de MyColl
        //simsignal_t MyCollSignal;
        //cOutVector MyCollVec;

    public:
        virtual void initialize(int stage);
        virtual void finish();
        double distance(const Coord& a, const Coord& b);

        enum WaveApplMessageKinds {
            CALC_CBR,
            PER_WSM
        };

    protected:
        simtime_t lastDroveAt;
        bool sentMessage;
        int currentSubscribedServiceId;

        /* state of the vehicle */
        double angleRad;

        Coord currposition;
        Coord currspeed;

        // Channel Busy Ratio
        double currCBR;
        double lastBusyT;

        // Neighbor list
        /*std::list<int> Neig;
        std::list<double> Utx_TrAD;*/

        mutable std::list < std::pair < double, int >> Neig;
        mutable std::list < std::pair < double, int >>::iterator it;

        mutable std::list < double > meanCBR;
        // Utx Neighbor, función de utilidad para TrAD
        double Utx_n;
        double Dij;

        // Ultimo Wsm recivido
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

        double calculateUtx(double CBR_n,double Dij_n, int Num_neig_n);
        std::list<std::pair<double,int>> replace(std::list<std::pair<double,int>>mylist,int addressSearch, double UtxReplace);
        bool isNeighbor(std::list<std::pair<double,int>>mylist,int addressSearch);
        int* makePriorList(std::list<std::pair<double,int>>mylist);
        void setingPLinWSM(int* list,WaveShortMessage* wsm);
        int getMyRank(WaveShortMessage* wsm, int my_id);
        double avg(std::list<double> list);


        cMessage* calcCBR_EV;
        cMessage* periodic_WSM_EV;

        uint32_t generatedWSMsSource;
    };

#endif /* MODULES_APPLICATION_MYWAVEAPPLAYER_H_ */
