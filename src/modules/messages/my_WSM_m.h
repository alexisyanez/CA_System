//
// Generated file, do not edit! Created by nedtool 5.1 from modules/messages/my_WSM.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __MY_WSM_M_H
#define __MY_WSM_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "veins/base/utils/Coord.h"
#include "modules/messages/WaveShortMessage_m.h"
// }}

/**
 * Class generated from <tt>modules/messages/my_WSM.msg:26</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet My_WSM extends WaveShortMessage
 * {
 *     Coord senderPos;
 *     Coord senderSpeed;
 *     double angleRad;
 *     int priorityList[]; // Orden calculado por el nodo fuente
 *     int Oirigin_ID;
 *     Coord Origin_pos;
 *     int ID;
 * }
 * </pre>
 */
class My_WSM : public ::WaveShortMessage
{
  protected:
    Coord senderPos;
    Coord senderSpeed;
    double angleRad;
    int *priorityList; // array ptr
    unsigned int priorityList_arraysize;
    int Oirigin_ID;
    Coord Origin_pos;
    int ID;

  private:
    void copy(const My_WSM& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const My_WSM&);

  public:
    My_WSM(const char *name=nullptr, short kind=0);
    My_WSM(const My_WSM& other);
    virtual ~My_WSM();
    My_WSM& operator=(const My_WSM& other);
    virtual My_WSM *dup() const override {return new My_WSM(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual Coord& getSenderPos();
    virtual const Coord& getSenderPos() const {return const_cast<My_WSM*>(this)->getSenderPos();}
    virtual void setSenderPos(const Coord& senderPos);
    virtual Coord& getSenderSpeed();
    virtual const Coord& getSenderSpeed() const {return const_cast<My_WSM*>(this)->getSenderSpeed();}
    virtual void setSenderSpeed(const Coord& senderSpeed);
    virtual double getAngleRad() const;
    virtual void setAngleRad(double angleRad);
    virtual void setPriorityListArraySize(unsigned int size);
    virtual unsigned int getPriorityListArraySize() const;
    virtual int getPriorityList(unsigned int k) const;
    virtual void setPriorityList(unsigned int k, int priorityList);
    virtual int getOirigin_ID() const;
    virtual void setOirigin_ID(int Oirigin_ID);
    virtual Coord& getOrigin_pos();
    virtual const Coord& getOrigin_pos() const {return const_cast<My_WSM*>(this)->getOrigin_pos();}
    virtual void setOrigin_pos(const Coord& Origin_pos);
    virtual int getID() const;
    virtual void setID(int ID);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const My_WSM& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, My_WSM& obj) {obj.parsimUnpack(b);}


#endif // ifndef __MY_WSM_M_H

