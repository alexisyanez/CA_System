//
// Generated file, do not edit! Created by nedtool 5.1 from modules/messages/my_WSM.msg.
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
#include "my_WSM_m.h"

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

Register_Class(My_WSM)

My_WSM::My_WSM(const char *name, short kind) : ::WaveShortMessage(name,kind)
{
    this->angleRad = 0;
    priorityList_arraysize = 0;
    this->priorityList = 0;
    this->Oirigin_ID = 0;
    this->ID = 0;
}

My_WSM::My_WSM(const My_WSM& other) : ::WaveShortMessage(other)
{
    priorityList_arraysize = 0;
    this->priorityList = 0;
    copy(other);
}

My_WSM::~My_WSM()
{
    delete [] this->priorityList;
}

My_WSM& My_WSM::operator=(const My_WSM& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void My_WSM::copy(const My_WSM& other)
{
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

void My_WSM::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WaveShortMessage::parsimPack(b);
    doParsimPacking(b,this->senderPos);
    doParsimPacking(b,this->senderSpeed);
    doParsimPacking(b,this->angleRad);
    b->pack(priorityList_arraysize);
    doParsimArrayPacking(b,this->priorityList,priorityList_arraysize);
    doParsimPacking(b,this->Oirigin_ID);
    doParsimPacking(b,this->Origin_pos);
    doParsimPacking(b,this->ID);
}

void My_WSM::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
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

Coord& My_WSM::getSenderPos()
{
    return this->senderPos;
}

void My_WSM::setSenderPos(const Coord& senderPos)
{
    this->senderPos = senderPos;
}

Coord& My_WSM::getSenderSpeed()
{
    return this->senderSpeed;
}

void My_WSM::setSenderSpeed(const Coord& senderSpeed)
{
    this->senderSpeed = senderSpeed;
}

double My_WSM::getAngleRad() const
{
    return this->angleRad;
}

void My_WSM::setAngleRad(double angleRad)
{
    this->angleRad = angleRad;
}

void My_WSM::setPriorityListArraySize(unsigned int size)
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

unsigned int My_WSM::getPriorityListArraySize() const
{
    return priorityList_arraysize;
}

int My_WSM::getPriorityList(unsigned int k) const
{
    if (k>=priorityList_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", priorityList_arraysize, k);
    return this->priorityList[k];
}

void My_WSM::setPriorityList(unsigned int k, int priorityList)
{
    if (k>=priorityList_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", priorityList_arraysize, k);
    this->priorityList[k] = priorityList;
}

int My_WSM::getOirigin_ID() const
{
    return this->Oirigin_ID;
}

void My_WSM::setOirigin_ID(int Oirigin_ID)
{
    this->Oirigin_ID = Oirigin_ID;
}

Coord& My_WSM::getOrigin_pos()
{
    return this->Origin_pos;
}

void My_WSM::setOrigin_pos(const Coord& Origin_pos)
{
    this->Origin_pos = Origin_pos;
}

int My_WSM::getID() const
{
    return this->ID;
}

void My_WSM::setID(int ID)
{
    this->ID = ID;
}

class My_WSMDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    My_WSMDescriptor();
    virtual ~My_WSMDescriptor();

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

Register_ClassDescriptor(My_WSMDescriptor)

My_WSMDescriptor::My_WSMDescriptor() : omnetpp::cClassDescriptor("My_WSM", "WaveShortMessage")
{
    propertynames = nullptr;
}

My_WSMDescriptor::~My_WSMDescriptor()
{
    delete[] propertynames;
}

bool My_WSMDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<My_WSM *>(obj)!=nullptr;
}

const char **My_WSMDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *My_WSMDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int My_WSMDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int My_WSMDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *My_WSMDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderPos",
        "senderSpeed",
        "angleRad",
        "priorityList",
        "Oirigin_ID",
        "Origin_pos",
        "ID",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int My_WSMDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderPos")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderSpeed")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "angleRad")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "priorityList")==0) return base+3;
    if (fieldName[0]=='O' && strcmp(fieldName, "Oirigin_ID")==0) return base+4;
    if (fieldName[0]=='O' && strcmp(fieldName, "Origin_pos")==0) return base+5;
    if (fieldName[0]=='I' && strcmp(fieldName, "ID")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *My_WSMDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "Coord",
        "Coord",
        "double",
        "int",
        "int",
        "Coord",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **My_WSMDescriptor::getFieldPropertyNames(int field) const
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

const char *My_WSMDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int My_WSMDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    My_WSM *pp = (My_WSM *)object; (void)pp;
    switch (field) {
        case 3: return pp->getPriorityListArraySize();
        default: return 0;
    }
}

const char *My_WSMDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    My_WSM *pp = (My_WSM *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string My_WSMDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    My_WSM *pp = (My_WSM *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSenderPos(); return out.str();}
        case 1: {std::stringstream out; out << pp->getSenderSpeed(); return out.str();}
        case 2: return double2string(pp->getAngleRad());
        case 3: return long2string(pp->getPriorityList(i));
        case 4: return long2string(pp->getOirigin_ID());
        case 5: {std::stringstream out; out << pp->getOrigin_pos(); return out.str();}
        case 6: return long2string(pp->getID());
        default: return "";
    }
}

bool My_WSMDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    My_WSM *pp = (My_WSM *)object; (void)pp;
    switch (field) {
        case 2: pp->setAngleRad(string2double(value)); return true;
        case 3: pp->setPriorityList(i,string2long(value)); return true;
        case 4: pp->setOirigin_ID(string2long(value)); return true;
        case 6: pp->setID(string2long(value)); return true;
        default: return false;
    }
}

const char *My_WSMDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(Coord));
        case 1: return omnetpp::opp_typename(typeid(Coord));
        case 5: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *My_WSMDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    My_WSM *pp = (My_WSM *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSenderPos()); break;
        case 1: return (void *)(&pp->getSenderSpeed()); break;
        case 5: return (void *)(&pp->getOrigin_pos()); break;
        default: return nullptr;
    }
}


