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

#ifndef __RINA_AEBASE_H_
#define __RINA_AEBASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "APNamingInfo.h"
#include "Flow.h"
#include "ExternConsts.h"
#include "QoSReq.h"

typedef std::list<Flow> Flows;
typedef Flows::iterator TFlowsIter;
//Consts

extern const char* PAR_AVGBW;
extern const char* PAR_AVGSDUBW;
extern const char* PAR_PEAKBWDUR;
extern const char* PAR_PEAKSDUBWDUR;
extern const char* PAR_BURSTPERIOD;
extern const char* PAR_BURSTDURATION;
extern const char* PAR_UNDETECTBITERR;
extern const char* PAR_PDUDROPPROBAB;
extern const char* PAR_MAXSDUSIZE;
extern const char* PAR_PARTIALDELIVER;
extern const char* PAR_INCOMPLETEDELIVER;
extern const char* PAR_FORCEORDER;
extern const char* PAR_MAXALLOWGAP;
extern const char* PAR_DELAY;
extern const char* PAR_JITTER;
extern const char* PAR_COSTTIME;
extern const char* PAR_COSTBITS;
extern const char* PAR_ATIME;


enum CDAPConnectionState {NIL,
    FLOW_PENDING, CONNECTION_PENDING,
    AUTHENTICATING, ESTABLISHED, RELEASING};

class AEBase : public cSimpleModule
{
  public:
    bool hasFlow(const Flow* flow);

    const APNamingInfo& getApni() const;

    bool operator== (const AEBase& other) {
        return (apni == other.apni);
    }

    const int getAuthType();
    const std::string& getAuthName() const;
    const std::string& getAuthPassword() const;
    const std::string& getAuthOther() const;
    void changeConStatus(CDAPConnectionState conState);
    CDAPConnectionState getConStatus();
    Flow* getFlowObject() const;
    void setFlowObject(Flow* flowObject);

  protected:
    //Flows flows;
    Flow* FlowObject;
    APNamingInfo apni;

    std::string srcApName;
    std::string srcApInstance;
    std::string srcAeName;
    std::string srcAeInstance;

    int authType;
    std::string authName;
    std::string authPassword;
    std::string authOther;

    QoSReq QoSRequirements;

    CDAPConnectionState connectionState;

    //Getters/Setters
    const std::string& getSrcAeInstance() const;
    void setSrcAeInstance(const std::string& srcAeInstance);
    const std::string& getSrcAeName() const;
    void setSrcAeName(const std::string& srcAeName);
    const std::string& getSrcApInstance() const;
    void setSrcApInstance(const std::string& srcApInstance);
    const std::string& getSrcApName() const;
    void setSrcApName(const std::string& srcApName);
    void setApni(const APNamingInfo& apni);
    void setFlows(const Flows& flows);
    const QoSReq& getQoSRequirements() const;
    void setQoSRequirements(const QoSReq& qoSRequirements);

    void initNamingInfo();
    void initQoSRequiremets();

    void insertFlow(Flow& flow);

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:

};

#endif
