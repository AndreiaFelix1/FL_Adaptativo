//
// Generated file, do not edit! Created by nedtool 5.7 from flexe/messages/FlexeMessage.msg.
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
#include <memory>
#include "FlexeMessage_m.h"

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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

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

Register_Class(FlexeMessage)

FlexeMessage::FlexeMessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

FlexeMessage::FlexeMessage(const FlexeMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

FlexeMessage::~FlexeMessage()
{
}

FlexeMessage& FlexeMessage::operator=(const FlexeMessage& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void FlexeMessage::copy(const FlexeMessage& other)
{
    this->senderID = other.senderID;
    this->model = other.model;
    this->msgId = other.msgId;
    this->sendTime = other.sendTime;
    this->dataset = other.dataset;
    this->scenario = other.scenario;
    this->seed = other.seed;
    this->nonIID = other.nonIID;
    this->idModel = other.idModel;
    this->trainFlag = other.trainFlag;
    this->dynamicEpoch = other.dynamicEpoch;
    this->numClients = other.numClients;
    this->percentDataset = other.percentDataset;
    this->numExamples = other.numExamples;
    this->modelVersion = other.modelVersion;
    this->clientSelection = other.clientSelection;
    this->loss = other.loss;
    this->accuracy = other.accuracy;
    this->precision = other.precision;
    this->recall = other.recall;
    this->f1Score = other.f1Score;
    this->mcc = other.mcc;
    this->aucRoc = other.aucRoc;
    this->tp = other.tp;
    this->fp = other.fp;
    this->tn = other.tn;
    this->fn = other.fn;
    this->entropy = other.entropy;
    this->computationCapability = other.computationCapability;
    this->computationRequirement = other.computationRequirement;
    this->roundDeadline = other.roundDeadline;
    this->color = other.color;
}

void FlexeMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->senderID);
    doParsimPacking(b,this->model);
    doParsimPacking(b,this->msgId);
    doParsimPacking(b,this->sendTime);
    doParsimPacking(b,this->dataset);
    doParsimPacking(b,this->scenario);
    doParsimPacking(b,this->seed);
    doParsimPacking(b,this->nonIID);
    doParsimPacking(b,this->idModel);
    doParsimPacking(b,this->trainFlag);
    doParsimPacking(b,this->dynamicEpoch);
    doParsimPacking(b,this->numClients);
    doParsimPacking(b,this->percentDataset);
    doParsimPacking(b,this->numExamples);
    doParsimPacking(b,this->modelVersion);
    doParsimPacking(b,this->clientSelection);
    doParsimPacking(b,this->loss);
    doParsimPacking(b,this->accuracy);
    doParsimPacking(b,this->precision);
    doParsimPacking(b,this->recall);
    doParsimPacking(b,this->f1Score);
    doParsimPacking(b,this->mcc);
    doParsimPacking(b,this->aucRoc);
    doParsimPacking(b,this->tp);
    doParsimPacking(b,this->fp);
    doParsimPacking(b,this->tn);
    doParsimPacking(b,this->fn);
    doParsimPacking(b,this->entropy);
    doParsimPacking(b,this->computationCapability);
    doParsimPacking(b,this->computationRequirement);
    doParsimPacking(b,this->roundDeadline);
    doParsimPacking(b,this->color);
}

void FlexeMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->senderID);
    doParsimUnpacking(b,this->model);
    doParsimUnpacking(b,this->msgId);
    doParsimUnpacking(b,this->sendTime);
    doParsimUnpacking(b,this->dataset);
    doParsimUnpacking(b,this->scenario);
    doParsimUnpacking(b,this->seed);
    doParsimUnpacking(b,this->nonIID);
    doParsimUnpacking(b,this->idModel);
    doParsimUnpacking(b,this->trainFlag);
    doParsimUnpacking(b,this->dynamicEpoch);
    doParsimUnpacking(b,this->numClients);
    doParsimUnpacking(b,this->percentDataset);
    doParsimUnpacking(b,this->numExamples);
    doParsimUnpacking(b,this->modelVersion);
    doParsimUnpacking(b,this->clientSelection);
    doParsimUnpacking(b,this->loss);
    doParsimUnpacking(b,this->accuracy);
    doParsimUnpacking(b,this->precision);
    doParsimUnpacking(b,this->recall);
    doParsimUnpacking(b,this->f1Score);
    doParsimUnpacking(b,this->mcc);
    doParsimUnpacking(b,this->aucRoc);
    doParsimUnpacking(b,this->tp);
    doParsimUnpacking(b,this->fp);
    doParsimUnpacking(b,this->tn);
    doParsimUnpacking(b,this->fn);
    doParsimUnpacking(b,this->entropy);
    doParsimUnpacking(b,this->computationCapability);
    doParsimUnpacking(b,this->computationRequirement);
    doParsimUnpacking(b,this->roundDeadline);
    doParsimUnpacking(b,this->color);
}

int FlexeMessage::getSenderID() const
{
    return this->senderID;
}

void FlexeMessage::setSenderID(int senderID)
{
    this->senderID = senderID;
}

const char * FlexeMessage::getModel() const
{
    return this->model.c_str();
}

void FlexeMessage::setModel(const char * model)
{
    this->model = model;
}

long FlexeMessage::getMsgId() const
{
    return this->msgId;
}

void FlexeMessage::setMsgId(long msgId)
{
    this->msgId = msgId;
}

double FlexeMessage::getSendTime() const
{
    return this->sendTime;
}

void FlexeMessage::setSendTime(double sendTime)
{
    this->sendTime = sendTime;
}

const char * FlexeMessage::getDataset() const
{
    return this->dataset.c_str();
}

void FlexeMessage::setDataset(const char * dataset)
{
    this->dataset = dataset;
}

const char * FlexeMessage::getScenario() const
{
    return this->scenario.c_str();
}

void FlexeMessage::setScenario(const char * scenario)
{
    this->scenario = scenario;
}

int FlexeMessage::getSeed() const
{
    return this->seed;
}

void FlexeMessage::setSeed(int seed)
{
    this->seed = seed;
}

bool FlexeMessage::getNonIID() const
{
    return this->nonIID;
}

void FlexeMessage::setNonIID(bool nonIID)
{
    this->nonIID = nonIID;
}

int FlexeMessage::getIdModel() const
{
    return this->idModel;
}

void FlexeMessage::setIdModel(int idModel)
{
    this->idModel = idModel;
}

bool FlexeMessage::getTrainFlag() const
{
    return this->trainFlag;
}

void FlexeMessage::setTrainFlag(bool trainFlag)
{
    this->trainFlag = trainFlag;
}

bool FlexeMessage::getDynamicEpoch() const
{
    return this->dynamicEpoch;
}

void FlexeMessage::setDynamicEpoch(bool dynamicEpoch)
{
    this->dynamicEpoch = dynamicEpoch;
}

int FlexeMessage::getNumClients() const
{
    return this->numClients;
}

void FlexeMessage::setNumClients(int numClients)
{
    this->numClients = numClients;
}

double FlexeMessage::getPercentDataset() const
{
    return this->percentDataset;
}

void FlexeMessage::setPercentDataset(double percentDataset)
{
    this->percentDataset = percentDataset;
}

int FlexeMessage::getNumExamples() const
{
    return this->numExamples;
}

void FlexeMessage::setNumExamples(int numExamples)
{
    this->numExamples = numExamples;
}

int FlexeMessage::getModelVersion() const
{
    return this->modelVersion;
}

void FlexeMessage::setModelVersion(int modelVersion)
{
    this->modelVersion = modelVersion;
}

const char * FlexeMessage::getClientSelection() const
{
    return this->clientSelection.c_str();
}

void FlexeMessage::setClientSelection(const char * clientSelection)
{
    this->clientSelection = clientSelection;
}

double FlexeMessage::getLoss() const
{
    return this->loss;
}

void FlexeMessage::setLoss(double loss)
{
    this->loss = loss;
}

double FlexeMessage::getAccuracy() const
{
    return this->accuracy;
}

void FlexeMessage::setAccuracy(double accuracy)
{
    this->accuracy = accuracy;
}

double FlexeMessage::getPrecision() const
{
    return this->precision;
}

void FlexeMessage::setPrecision(double precision)
{
    this->precision = precision;
}

double FlexeMessage::getRecall() const
{
    return this->recall;
}

void FlexeMessage::setRecall(double recall)
{
    this->recall = recall;
}

double FlexeMessage::getF1Score() const
{
    return this->f1Score;
}

void FlexeMessage::setF1Score(double f1Score)
{
    this->f1Score = f1Score;
}

double FlexeMessage::getMcc() const
{
    return this->mcc;
}

void FlexeMessage::setMcc(double mcc)
{
    this->mcc = mcc;
}

double FlexeMessage::getAucRoc() const
{
    return this->aucRoc;
}

void FlexeMessage::setAucRoc(double aucRoc)
{
    this->aucRoc = aucRoc;
}

int FlexeMessage::getTp() const
{
    return this->tp;
}

void FlexeMessage::setTp(int tp)
{
    this->tp = tp;
}

int FlexeMessage::getFp() const
{
    return this->fp;
}

void FlexeMessage::setFp(int fp)
{
    this->fp = fp;
}

int FlexeMessage::getTn() const
{
    return this->tn;
}

void FlexeMessage::setTn(int tn)
{
    this->tn = tn;
}

int FlexeMessage::getFn() const
{
    return this->fn;
}

void FlexeMessage::setFn(int fn)
{
    this->fn = fn;
}

double FlexeMessage::getEntropy() const
{
    return this->entropy;
}

void FlexeMessage::setEntropy(double entropy)
{
    this->entropy = entropy;
}

double FlexeMessage::getComputationCapability() const
{
    return this->computationCapability;
}

void FlexeMessage::setComputationCapability(double computationCapability)
{
    this->computationCapability = computationCapability;
}

double FlexeMessage::getComputationRequirement() const
{
    return this->computationRequirement;
}

void FlexeMessage::setComputationRequirement(double computationRequirement)
{
    this->computationRequirement = computationRequirement;
}

double FlexeMessage::getRoundDeadline() const
{
    return this->roundDeadline;
}

void FlexeMessage::setRoundDeadline(double roundDeadline)
{
    this->roundDeadline = roundDeadline;
}

const char * FlexeMessage::getColor() const
{
    return this->color.c_str();
}

void FlexeMessage::setColor(const char * color)
{
    this->color = color;
}

class FlexeMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_senderID,
        FIELD_model,
        FIELD_msgId,
        FIELD_sendTime,
        FIELD_dataset,
        FIELD_scenario,
        FIELD_seed,
        FIELD_nonIID,
        FIELD_idModel,
        FIELD_trainFlag,
        FIELD_dynamicEpoch,
        FIELD_numClients,
        FIELD_percentDataset,
        FIELD_numExamples,
        FIELD_modelVersion,
        FIELD_clientSelection,
        FIELD_loss,
        FIELD_accuracy,
        FIELD_precision,
        FIELD_recall,
        FIELD_f1Score,
        FIELD_mcc,
        FIELD_aucRoc,
        FIELD_tp,
        FIELD_fp,
        FIELD_tn,
        FIELD_fn,
        FIELD_entropy,
        FIELD_computationCapability,
        FIELD_computationRequirement,
        FIELD_roundDeadline,
        FIELD_color,
    };
  public:
    FlexeMessageDescriptor();
    virtual ~FlexeMessageDescriptor();

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

Register_ClassDescriptor(FlexeMessageDescriptor)

FlexeMessageDescriptor::FlexeMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(FlexeMessage)), "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

FlexeMessageDescriptor::~FlexeMessageDescriptor()
{
    delete[] propertynames;
}

bool FlexeMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlexeMessage *>(obj)!=nullptr;
}

const char **FlexeMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlexeMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlexeMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 32+basedesc->getFieldCount() : 32;
}

unsigned int FlexeMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_senderID
        FD_ISEDITABLE,    // FIELD_model
        FD_ISEDITABLE,    // FIELD_msgId
        FD_ISEDITABLE,    // FIELD_sendTime
        FD_ISEDITABLE,    // FIELD_dataset
        FD_ISEDITABLE,    // FIELD_scenario
        FD_ISEDITABLE,    // FIELD_seed
        FD_ISEDITABLE,    // FIELD_nonIID
        FD_ISEDITABLE,    // FIELD_idModel
        FD_ISEDITABLE,    // FIELD_trainFlag
        FD_ISEDITABLE,    // FIELD_dynamicEpoch
        FD_ISEDITABLE,    // FIELD_numClients
        FD_ISEDITABLE,    // FIELD_percentDataset
        FD_ISEDITABLE,    // FIELD_numExamples
        FD_ISEDITABLE,    // FIELD_modelVersion
        FD_ISEDITABLE,    // FIELD_clientSelection
        FD_ISEDITABLE,    // FIELD_loss
        FD_ISEDITABLE,    // FIELD_accuracy
        FD_ISEDITABLE,    // FIELD_precision
        FD_ISEDITABLE,    // FIELD_recall
        FD_ISEDITABLE,    // FIELD_f1Score
        FD_ISEDITABLE,    // FIELD_mcc
        FD_ISEDITABLE,    // FIELD_aucRoc
        FD_ISEDITABLE,    // FIELD_tp
        FD_ISEDITABLE,    // FIELD_fp
        FD_ISEDITABLE,    // FIELD_tn
        FD_ISEDITABLE,    // FIELD_fn
        FD_ISEDITABLE,    // FIELD_entropy
        FD_ISEDITABLE,    // FIELD_computationCapability
        FD_ISEDITABLE,    // FIELD_computationRequirement
        FD_ISEDITABLE,    // FIELD_roundDeadline
        FD_ISEDITABLE,    // FIELD_color
    };
    return (field >= 0 && field < 32) ? fieldTypeFlags[field] : 0;
}

const char *FlexeMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderID",
        "model",
        "msgId",
        "sendTime",
        "dataset",
        "scenario",
        "seed",
        "nonIID",
        "idModel",
        "trainFlag",
        "dynamicEpoch",
        "numClients",
        "percentDataset",
        "numExamples",
        "modelVersion",
        "clientSelection",
        "loss",
        "accuracy",
        "precision",
        "recall",
        "f1Score",
        "mcc",
        "aucRoc",
        "tp",
        "fp",
        "tn",
        "fn",
        "entropy",
        "computationCapability",
        "computationRequirement",
        "roundDeadline",
        "color",
    };
    return (field >= 0 && field < 32) ? fieldNames[field] : nullptr;
}

int FlexeMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderID") == 0) return base+0;
    if (fieldName[0] == 'm' && strcmp(fieldName, "model") == 0) return base+1;
    if (fieldName[0] == 'm' && strcmp(fieldName, "msgId") == 0) return base+2;
    if (fieldName[0] == 's' && strcmp(fieldName, "sendTime") == 0) return base+3;
    if (fieldName[0] == 'd' && strcmp(fieldName, "dataset") == 0) return base+4;
    if (fieldName[0] == 's' && strcmp(fieldName, "scenario") == 0) return base+5;
    if (fieldName[0] == 's' && strcmp(fieldName, "seed") == 0) return base+6;
    if (fieldName[0] == 'n' && strcmp(fieldName, "nonIID") == 0) return base+7;
    if (fieldName[0] == 'i' && strcmp(fieldName, "idModel") == 0) return base+8;
    if (fieldName[0] == 't' && strcmp(fieldName, "trainFlag") == 0) return base+9;
    if (fieldName[0] == 'd' && strcmp(fieldName, "dynamicEpoch") == 0) return base+10;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numClients") == 0) return base+11;
    if (fieldName[0] == 'p' && strcmp(fieldName, "percentDataset") == 0) return base+12;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numExamples") == 0) return base+13;
    if (fieldName[0] == 'm' && strcmp(fieldName, "modelVersion") == 0) return base+14;
    if (fieldName[0] == 'c' && strcmp(fieldName, "clientSelection") == 0) return base+15;
    if (fieldName[0] == 'l' && strcmp(fieldName, "loss") == 0) return base+16;
    if (fieldName[0] == 'a' && strcmp(fieldName, "accuracy") == 0) return base+17;
    if (fieldName[0] == 'p' && strcmp(fieldName, "precision") == 0) return base+18;
    if (fieldName[0] == 'r' && strcmp(fieldName, "recall") == 0) return base+19;
    if (fieldName[0] == 'f' && strcmp(fieldName, "f1Score") == 0) return base+20;
    if (fieldName[0] == 'm' && strcmp(fieldName, "mcc") == 0) return base+21;
    if (fieldName[0] == 'a' && strcmp(fieldName, "aucRoc") == 0) return base+22;
    if (fieldName[0] == 't' && strcmp(fieldName, "tp") == 0) return base+23;
    if (fieldName[0] == 'f' && strcmp(fieldName, "fp") == 0) return base+24;
    if (fieldName[0] == 't' && strcmp(fieldName, "tn") == 0) return base+25;
    if (fieldName[0] == 'f' && strcmp(fieldName, "fn") == 0) return base+26;
    if (fieldName[0] == 'e' && strcmp(fieldName, "entropy") == 0) return base+27;
    if (fieldName[0] == 'c' && strcmp(fieldName, "computationCapability") == 0) return base+28;
    if (fieldName[0] == 'c' && strcmp(fieldName, "computationRequirement") == 0) return base+29;
    if (fieldName[0] == 'r' && strcmp(fieldName, "roundDeadline") == 0) return base+30;
    if (fieldName[0] == 'c' && strcmp(fieldName, "color") == 0) return base+31;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlexeMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_senderID
        "string",    // FIELD_model
        "long",    // FIELD_msgId
        "double",    // FIELD_sendTime
        "string",    // FIELD_dataset
        "string",    // FIELD_scenario
        "int",    // FIELD_seed
        "bool",    // FIELD_nonIID
        "int",    // FIELD_idModel
        "bool",    // FIELD_trainFlag
        "bool",    // FIELD_dynamicEpoch
        "int",    // FIELD_numClients
        "double",    // FIELD_percentDataset
        "int",    // FIELD_numExamples
        "int",    // FIELD_modelVersion
        "string",    // FIELD_clientSelection
        "double",    // FIELD_loss
        "double",    // FIELD_accuracy
        "double",    // FIELD_precision
        "double",    // FIELD_recall
        "double",    // FIELD_f1Score
        "double",    // FIELD_mcc
        "double",    // FIELD_aucRoc
        "int",    // FIELD_tp
        "int",    // FIELD_fp
        "int",    // FIELD_tn
        "int",    // FIELD_fn
        "double",    // FIELD_entropy
        "double",    // FIELD_computationCapability
        "double",    // FIELD_computationRequirement
        "double",    // FIELD_roundDeadline
        "string",    // FIELD_color
    };
    return (field >= 0 && field < 32) ? fieldTypeStrings[field] : nullptr;
}

const char **FlexeMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *FlexeMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int FlexeMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FlexeMessage *pp = (FlexeMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FlexeMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlexeMessage *pp = (FlexeMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlexeMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FlexeMessage *pp = (FlexeMessage *)object; (void)pp;
    switch (field) {
        case FIELD_senderID: return long2string(pp->getSenderID());
        case FIELD_model: return oppstring2string(pp->getModel());
        case FIELD_msgId: return long2string(pp->getMsgId());
        case FIELD_sendTime: return double2string(pp->getSendTime());
        case FIELD_dataset: return oppstring2string(pp->getDataset());
        case FIELD_scenario: return oppstring2string(pp->getScenario());
        case FIELD_seed: return long2string(pp->getSeed());
        case FIELD_nonIID: return bool2string(pp->getNonIID());
        case FIELD_idModel: return long2string(pp->getIdModel());
        case FIELD_trainFlag: return bool2string(pp->getTrainFlag());
        case FIELD_dynamicEpoch: return bool2string(pp->getDynamicEpoch());
        case FIELD_numClients: return long2string(pp->getNumClients());
        case FIELD_percentDataset: return double2string(pp->getPercentDataset());
        case FIELD_numExamples: return long2string(pp->getNumExamples());
        case FIELD_modelVersion: return long2string(pp->getModelVersion());
        case FIELD_clientSelection: return oppstring2string(pp->getClientSelection());
        case FIELD_loss: return double2string(pp->getLoss());
        case FIELD_accuracy: return double2string(pp->getAccuracy());
        case FIELD_precision: return double2string(pp->getPrecision());
        case FIELD_recall: return double2string(pp->getRecall());
        case FIELD_f1Score: return double2string(pp->getF1Score());
        case FIELD_mcc: return double2string(pp->getMcc());
        case FIELD_aucRoc: return double2string(pp->getAucRoc());
        case FIELD_tp: return long2string(pp->getTp());
        case FIELD_fp: return long2string(pp->getFp());
        case FIELD_tn: return long2string(pp->getTn());
        case FIELD_fn: return long2string(pp->getFn());
        case FIELD_entropy: return double2string(pp->getEntropy());
        case FIELD_computationCapability: return double2string(pp->getComputationCapability());
        case FIELD_computationRequirement: return double2string(pp->getComputationRequirement());
        case FIELD_roundDeadline: return double2string(pp->getRoundDeadline());
        case FIELD_color: return oppstring2string(pp->getColor());
        default: return "";
    }
}

bool FlexeMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FlexeMessage *pp = (FlexeMessage *)object; (void)pp;
    switch (field) {
        case FIELD_senderID: pp->setSenderID(string2long(value)); return true;
        case FIELD_model: pp->setModel((value)); return true;
        case FIELD_msgId: pp->setMsgId(string2long(value)); return true;
        case FIELD_sendTime: pp->setSendTime(string2double(value)); return true;
        case FIELD_dataset: pp->setDataset((value)); return true;
        case FIELD_scenario: pp->setScenario((value)); return true;
        case FIELD_seed: pp->setSeed(string2long(value)); return true;
        case FIELD_nonIID: pp->setNonIID(string2bool(value)); return true;
        case FIELD_idModel: pp->setIdModel(string2long(value)); return true;
        case FIELD_trainFlag: pp->setTrainFlag(string2bool(value)); return true;
        case FIELD_dynamicEpoch: pp->setDynamicEpoch(string2bool(value)); return true;
        case FIELD_numClients: pp->setNumClients(string2long(value)); return true;
        case FIELD_percentDataset: pp->setPercentDataset(string2double(value)); return true;
        case FIELD_numExamples: pp->setNumExamples(string2long(value)); return true;
        case FIELD_modelVersion: pp->setModelVersion(string2long(value)); return true;
        case FIELD_clientSelection: pp->setClientSelection((value)); return true;
        case FIELD_loss: pp->setLoss(string2double(value)); return true;
        case FIELD_accuracy: pp->setAccuracy(string2double(value)); return true;
        case FIELD_precision: pp->setPrecision(string2double(value)); return true;
        case FIELD_recall: pp->setRecall(string2double(value)); return true;
        case FIELD_f1Score: pp->setF1Score(string2double(value)); return true;
        case FIELD_mcc: pp->setMcc(string2double(value)); return true;
        case FIELD_aucRoc: pp->setAucRoc(string2double(value)); return true;
        case FIELD_tp: pp->setTp(string2long(value)); return true;
        case FIELD_fp: pp->setFp(string2long(value)); return true;
        case FIELD_tn: pp->setTn(string2long(value)); return true;
        case FIELD_fn: pp->setFn(string2long(value)); return true;
        case FIELD_entropy: pp->setEntropy(string2double(value)); return true;
        case FIELD_computationCapability: pp->setComputationCapability(string2double(value)); return true;
        case FIELD_computationRequirement: pp->setComputationRequirement(string2double(value)); return true;
        case FIELD_roundDeadline: pp->setRoundDeadline(string2double(value)); return true;
        case FIELD_color: pp->setColor((value)); return true;
        default: return false;
    }
}

const char *FlexeMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *FlexeMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FlexeMessage *pp = (FlexeMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

