//
// Generated file, do not edit! Created by nedtool 5.1 from modules/messages/WaveShortMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "WaveShortMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(WaveShortMessage)

WaveShortMessage::WaveShortMessage(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->wsmVersion = 0;
    this->securityType = 0;
    this->channelNumber = 0;
    this->dataRate = 1;
    this->userPriority = 7;
    this->psid = 0;
    this->psc = "Service with some Data";
    this->wsmLength = 0;
    this->wsmData = "Some Data";
    this->senderAddress = 0;
    this->recipientAddress = -1;
    this->serial = 0;
    this->timestamp = 0;
    this->angleRad = -1;
    priorityList_arraysize = 0;
    this->priorityList = 0;
    this->Oirigin_ID = -1;
    this->ID = -1;
}

WaveShortMessage::WaveShortMessage(const WaveShortMessage& other) : ::omnetpp::cPacket(other)
{
    priorityList_arraysize = 0;
    this->priorityList = 0;
    copy(other);
}

WaveShortMessage::~WaveShortMessage()
{
    delete [] this->priorityList;
}

WaveShortMessage& WaveShortMessage::operator=(const WaveShortMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WaveShortMessage::copy(const WaveShortMessage& other)
{
    this->wsmVersion = other.wsmVersion;
    this->securityType = other.securityType;
    this->channelNumber = other.channelNumber;
    this->dataRate = other.dataRate;
    this->userPriority = other.userPriority;
    this->psid = other.psid;
    this->psc = other.psc;
    this->wsmLength = other.wsmLength;
    this->wsmData = other.wsmData;
    this->senderAddress = other.senderAddress;
    this->recipientAddress = other.recipientAddress;
    this->serial = other.serial;
    this->timestamp = other.timestamp;
    this->senderPos = other.senderPos;
    this->senderSpeed = other.senderSpeed;
    this->angleRad = other.angleRad;
    delete [] this->priorityList;
    this->priorityList = (other.priorityList_arraysize==0) ? nullptr : new int[other.priorityList_arraysize];
    priorityList_arraysize = other.priorityList_arraysize;
    for (unsigned int i=0; i<priorityList_arraysize; i++)
        this->priorityList[i] = other.priorityList[i];
    this->Oirigin_ID = other.Oirigin_ID;
    this->Origin_pos = other.Origin_pos;
    this->ID = other.ID;
}

void WaveShortMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->wsmVersion);
    doParsimPacking(b,this->securityType);
    doParsimPacking(b,this->channelNumber);
    doParsimPacking(b,this->dataRate);
    doParsimPacking(b,this->userPriority);
    doParsimPacking(b,this->psid);
    doParsimPacking(b,this->psc);
    doParsimPacking(b,this->wsmLength);
    doParsimPacking(b,this->wsmData);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->recipientAddress);
    doParsimPacking(b,this->serial);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->senderPos);
    doParsimPacking(b,this->senderSpeed);
    doParsimPacking(b,this->angleRad);
    b->pack(priorityList_arraysize);
    doParsimArrayPacking(b,this->priorityList,priorityList_arraysize);
    doParsimPacking(b,this->Oirigin_ID);
    doParsimPacking(b,this->Origin_pos);
    doParsimPacking(b,this->ID);
}

void WaveShortMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->wsmVersion);
    doParsimUnpacking(b,this->securityType);
    doParsimUnpacking(b,this->channelNumber);
    doParsimUnpacking(b,this->dataRate);
    doParsimUnpacking(b,this->userPriority);
    doParsimUnpacking(b,this->psid);
    doParsimUnpacking(b,this->psc);
    doParsimUnpacking(b,this->wsmLength);
    doParsimUnpacking(b,this->wsmData);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->recipientAddress);
    doParsimUnpacking(b,this->serial);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->senderPos);
    doParsimUnpacking(b,this->senderSpeed);
    doParsimUnpacking(b,this->angleRad);
    delete [] this->priorityList;
    b->unpack(priorityList_arraysize);
    if (priorityList_arraysize==0) {
        this->priorityList = 0;
    } else {
        this->priorityList = new int[priorityList_arraysize];
        doParsimArrayUnpacking(b,this->priorityList,priorityList_arraysize);
    }
    doParsimUnpacking(b,this->Oirigin_ID);
    doParsimUnpacking(b,this->Origin_pos);
    doParsimUnpacking(b,this->ID);
}

int WaveShortMessage::getWsmVersion() const
{
    return this->wsmVersion;
}

void WaveShortMessage::setWsmVersion(int wsmVersion)
{
    this->wsmVersion = wsmVersion;
}

int WaveShortMessage::getSecurityType() const
{
    return this->securityType;
}

void WaveShortMessage::setSecurityType(int securityType)
{
    this->securityType = securityType;
}

int WaveShortMessage::getChannelNumber() const
{
    return this->channelNumber;
}

void WaveShortMessage::setChannelNumber(int channelNumber)
{
    this->channelNumber = channelNumber;
}

int WaveShortMessage::getDataRate() const
{
    return this->dataRate;
}

void WaveShortMessage::setDataRate(int dataRate)
{
    this->dataRate = dataRate;
}

int WaveShortMessage::getUserPriority() const
{
    return this->userPriority;
}

void WaveShortMessage::setUserPriority(int userPriority)
{
    this->userPriority = userPriority;
}

int WaveShortMessage::getPsid() const
{
    return this->psid;
}

void WaveShortMessage::setPsid(int psid)
{
    this->psid = psid;
}

const char * WaveShortMessage::getPsc() const
{
    return this->psc.c_str();
}

void WaveShortMessage::setPsc(const char * psc)
{
    this->psc = psc;
}

int WaveShortMessage::getWsmLength() const
{
    return this->wsmLength;
}

void WaveShortMessage::setWsmLength(int wsmLength)
{
    this->wsmLength = wsmLength;
}

const char * WaveShortMessage::getWsmData() const
{
    return this->wsmData.c_str();
}

void WaveShortMessage::setWsmData(const char * wsmData)
{
    this->wsmData = wsmData;
}

int WaveShortMessage::getSenderAddress() const
{
    return this->senderAddress;
}

void WaveShortMessage::setSenderAddress(int senderAddress)
{
    this->senderAddress = senderAddress;
}

int WaveShortMessage::getRecipientAddress() const
{
    return this->recipientAddress;
}

void WaveShortMessage::setRecipientAddress(int recipientAddress)
{
    this->recipientAddress = recipientAddress;
}

int WaveShortMessage::getSerial() const
{
    return this->serial;
}

void WaveShortMessage::setSerial(int serial)
{
    this->serial = serial;
}

::omnetpp::simtime_t WaveShortMessage::getTimestamp() const
{
    return this->timestamp;
}

void WaveShortMessage::setTimestamp(::omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

Coord& WaveShortMessage::getSenderPos()
{
    return this->senderPos;
}

void WaveShortMessage::setSenderPos(const Coord& senderPos)
{
    this->senderPos = senderPos;
}

Coord& WaveShortMessage::getSenderSpeed()
{
    return this->senderSpeed;
}

void WaveShortMessage::setSenderSpeed(const Coord& senderSpeed)
{
    this->senderSpeed = senderSpeed;
}

double WaveShortMessage::getAngleRad() const
{
    return this->angleRad;
}

void WaveShortMessage::setAngleRad(double angleRad)
{
    this->angleRad = angleRad;
}

void WaveShortMessage::setPriorityListArraySize(unsigned int size)
{
    int *priorityList2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = priorityList_arraysize < size ? priorityList_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        priorityList2[i] = this->priorityList[i];
    for (unsigned int i=sz; i<size; i++)
        priorityList2[i] = 0;
    priorityList_arraysize = size;
    delete [] this->priorityList;
    this->priorityList = priorityList2;
}

unsigned int WaveShortMessage::getPriorityListArraySize() const
{
    return priorityList_arraysize;
}

int WaveShortMessage::getPriorityList(unsigned int k) const
{
    if (k>=priorityList_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", priorityList_arraysize, k);
    return this->priorityList[k];
}

void WaveShortMessage::setPriorityList(unsigned int k, int priorityList)
{
    if (k>=priorityList_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", priorityList_arraysize, k);
    this->priorityList[k] = priorityList;
}

int WaveShortMessage::getOirigin_ID() const
{
    return this->Oirigin_ID;
}

void WaveShortMessage::setOirigin_ID(int Oirigin_ID)
{
    this->Oirigin_ID = Oirigin_ID;
}

Coord& WaveShortMessage::getOrigin_pos()
{
    return this->Origin_pos;
}

void WaveShortMessage::setOrigin_pos(const Coord& Origin_pos)
{
    this->Origin_pos = Origin_pos;
}

int WaveShortMessage::getID() const
{
    return this->ID;
}

void WaveShortMessage::setID(int ID)
{
    this->ID = ID;
}

class WaveShortMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WaveShortMessageDescriptor();
    virtual ~WaveShortMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WaveShortMessageDescriptor)

WaveShortMessageDescriptor::WaveShortMessageDescriptor() : omnetpp::cClassDescriptor("WaveShortMessage", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WaveShortMessageDescriptor::~WaveShortMessageDescriptor()
{
    delete[] propertynames;
}

bool WaveShortMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WaveShortMessage *>(obj)!=nullptr;
}

const char **WaveShortMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WaveShortMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WaveShortMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 20+basedesc->getFieldCount() : 20;
}

unsigned int WaveShortMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<20) ? fieldTypeFlags[field] : 0;
}

const char *WaveShortMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "wsmVersion",
        "securityType",
        "channelNumber",
        "dataRate",
        "userPriority",
        "psid",
        "psc",
        "wsmLength",
        "wsmData",
        "senderAddress",
        "recipientAddress",
        "serial",
        "timestamp",
        "senderPos",
        "senderSpeed",
        "angleRad",
        "priorityList",
        "Oirigin_ID",
        "Origin_pos",
        "ID",
    };
    return (field>=0 && field<20) ? fieldNames[field] : nullptr;
}

int WaveShortMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='w' && strcmp(fieldName, "wsmVersion")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "securityType")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "channelNumber")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataRate")==0) return base+3;
    if (fieldName[0]=='u' && strcmp(fieldName, "userPriority")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "psid")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "psc")==0) return base+6;
    if (fieldName[0]=='w' && strcmp(fieldName, "wsmLength")==0) return base+7;
    if (fieldName[0]=='w' && strcmp(fieldName, "wsmData")==0) return base+8;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+9;
    if (fieldName[0]=='r' && strcmp(fieldName, "recipientAddress")==0) return base+10;
    if (fieldName[0]=='s' && strcmp(fieldName, "serial")==0) return base+11;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+12;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderPos")==0) return base+13;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderSpeed")==0) return base+14;
    if (fieldName[0]=='a' && strcmp(fieldName, "angleRad")==0) return base+15;
    if (fieldName[0]=='p' && strcmp(fieldName, "priorityList")==0) return base+16;
    if (fieldName[0]=='O' && strcmp(fieldName, "Oirigin_ID")==0) return base+17;
    if (fieldName[0]=='O' && strcmp(fieldName, "Origin_pos")==0) return base+18;
    if (fieldName[0]=='I' && strcmp(fieldName, "ID")==0) return base+19;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WaveShortMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "string",
        "int",
        "string",
        "int",
        "int",
        "int",
        "simtime_t",
        "Coord",
        "Coord",
        "double",
        "int",
        "int",
        "Coord",
        "int",
    };
    return (field>=0 && field<20) ? fieldTypeStrings[field] : nullptr;
}

const char **WaveShortMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WaveShortMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WaveShortMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WaveShortMessage *pp = (WaveShortMessage *)object; (void)pp;
    switch (field) {
        case 16: return pp->getPriorityListArraySize();
        default: return 0;
    }
}

const char *WaveShortMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WaveShortMessage *pp = (WaveShortMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WaveShortMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WaveShortMessage *pp = (WaveShortMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getWsmVersion());
        case 1: return long2string(pp->getSecurityType());
        case 2: return long2string(pp->getChannelNumber());
        case 3: return long2string(pp->getDataRate());
        case 4: return long2string(pp->getUserPriority());
        case 5: return long2string(pp->getPsid());
        case 6: return oppstring2string(pp->getPsc());
        case 7: return long2string(pp->getWsmLength());
        case 8: return oppstring2string(pp->getWsmData());
        case 9: return long2string(pp->getSenderAddress());
        case 10: return long2string(pp->getRecipientAddress());
        case 11: return long2string(pp->getSerial());
        case 12: return simtime2string(pp->getTimestamp());
        case 13: {std::stringstream out; out << pp->getSenderPos(); return out.str();}
        case 14: {std::stringstream out; out << pp->getSenderSpeed(); return out.str();}
        case 15: return double2string(pp->getAngleRad());
        case 16: return long2string(pp->getPriorityList(i));
        case 17: return long2string(pp->getOirigin_ID());
        case 18: {std::stringstream out; out << pp->getOrigin_pos(); return out.str();}
        case 19: return long2string(pp->getID());
        default: return "";
    }
}

bool WaveShortMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WaveShortMessage *pp = (WaveShortMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setWsmVersion(string2long(value)); return true;
        case 1: pp->setSecurityType(string2long(value)); return true;
        case 2: pp->setChannelNumber(string2long(value)); return true;
        case 3: pp->setDataRate(string2long(value)); return true;
        case 4: pp->setUserPriority(string2long(value)); return true;
        case 5: pp->setPsid(string2long(value)); return true;
        case 6: pp->setPsc((value)); return true;
        case 7: pp->setWsmLength(string2long(value)); return true;
        case 8: pp->setWsmData((value)); return true;
        case 9: pp->setSenderAddress(string2long(value)); return true;
        case 10: pp->setRecipientAddress(string2long(value)); return true;
        case 11: pp->setSerial(string2long(value)); return true;
        case 12: pp->setTimestamp(string2simtime(value)); return true;
        case 15: pp->setAngleRad(string2double(value)); return true;
        case 16: pp->setPriorityList(i,string2long(value)); return true;
        case 17: pp->setOirigin_ID(string2long(value)); return true;
        case 19: pp->setID(string2long(value)); return true;
        default: return false;
    }
}

const char *WaveShortMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 13: return omnetpp::opp_typename(typeid(Coord));
        case 14: return omnetpp::opp_typename(typeid(Coord));
        case 18: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *WaveShortMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WaveShortMessage *pp = (WaveShortMessage *)object; (void)pp;
    switch (field) {
        case 13: return (void *)(&pp->getSenderPos()); break;
        case 14: return (void *)(&pp->getSenderSpeed()); break;
        case 18: return (void *)(&pp->getOrigin_pos()); break;
        default: return nullptr;
    }
}


