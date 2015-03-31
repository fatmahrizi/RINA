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

#ifndef DTP_H_
#define DTP_H_

#include <omnetpp.h>
#include <vector>

#include "DTPState.h"
#include "DTPTimers_m.h"
#include "DTCP.h"
//#include "PDU.h"
#include "DataTransferPDU.h"
#include "ControlPDU_m.h"
#include "SDU.h"
#include "RMT.h"

#include "RA.h"


/* Policies */
#include "DTPRcvrInactivityPolicyBase.h"
#include "DTPSenderInactivityPolicyBase.h"
#include "DTPInitialSeqNumPolicyBase.h"
#include "DTPRTTEstimatorPolicyBase.h"

//#include "SDUs.h"

#define DTP_MODULE_NAME "dtp"
#define DEFAULT_INIT_SEQUENCE_NUMBER 1


class DTCP;

class DTP : public cSimpleModule
{

    friend class DTCP;
  private:

    int deletePdu;
    bool pduDroppingEnabled;

    DTPState* state; //state of this data-transfer
    DTCP* dtcp;
    Flow* flow;

//    const QoSCube *qosCube;

    /* Policies */
    DTPRcvrInactivityPolicyBase* rcvrInactivityPolicy;
    DTPSenderInactivityPolicyBase* senderInactivityPolicy;
    DTPInitialSeqNumPolicyBase* initialSeqNumPolicy;
    DTPRTTEstimatorPolicyBase* rttEstimatorPolicy;

    /* Various queues */
    /* Output queues - from App to RMT */
    std::vector<SDU*> sduQ; //SDUs generated from delimiting //TODO A1 Deprecated - delete
    std::vector<SDU*> dataQ; //SDU or SDUFragments generated from delimiting



    /* Timers */
    SenderInactivityTimer* senderInactivityTimer;
    RcvrInactivityTimer* rcvrInactivityTimer;

    /**************** Moved rateFulfilled to FC together with sendingRatetimer **************************/
    /* This timer should be in FlowControl, but since for some reason "rateFulfilled" is in DTState it is better available from here */
//    SendingRateTimer* sendingRateTimer;

//    WindowTimer* windowTimer;

    /* Gates */
    /* To FAI */
    cGate* northI;
    cGate* northO;

    /* To RMT */
    cGate* southI;
    cGate* southO;

    ConnectionId connId;

    /* Handle messages and timer */
//    void handleDTPRxExpiryTimer(RxExpiryTimer* timer);
//    void handleDTPSendingRateTimer(SendingRateTimer* timer);
//    void handleDTPWindowTimer(WindowTimer* timer);
    void handleDTPRcvrInactivityTimer(RcvrInactivityTimer* timer);
    void handleDTPSenderInactivityTimer(SenderInactivityTimer* timer);
    void handleDTPATimer(ATimer* timer);

//    void handleMsgFromDelimiting(Data* msg);
    void handleMsgFromDelimiting(SDU* sdu);
    void handleMsgFromRMT(PDU* msg);
    void handleDataTransferPDUFromRMT(DataTransferPDU* pdu);

    /* Send */


    /** Delimits content of buffer from application */
    unsigned int delimit(SDU* sdu);
    unsigned int delimitFromRMT(PDU *pdu, unsigned int len);


    /** Encapsulate all SDUs from sduQ into PDUs and put them in generated_PDU Queue */
    void generatePDUsnew();

    void trySendGenPDUs(std::vector<DataTransferPDU*>* pduQ);



    /** This method does SDU protection eg CRC*/
    void sduProtection(SDU *sdu);

    void getSDUFromQ(SDU *sdu);


    void setConnId(const ConnectionId& connId);

    /* Policies */


    /* Policy-related methods */
//    void runTxControlPolicy(std::vector<DataTransferPDU*>* pduQ);
//    void runNoRateSlowDownPolicy();
//    void runReconcileFlowControlPolicy();
    bool runInitialSeqNumPolicy();
//    void runRateReductionPolicy();
//    void runRxTimerExpiryPolicy(RxExpiryTimer* timer);
    void runRcvrInactivityTimerPolicy();
    void runSenderInactivityTimerPolicy();
    void runRTTEstimatorPolicy();





    unsigned int getFlowControlRightWinEdge();

    /* This method SHOULD return amount of time to wait before retransmission attempt */
    double getRxTime();

    unsigned int getAllowableGap();

    void svUpdate(unsigned int seqNum);

    void flushReassemblyPDUQ();
    void clearRxQ();
    void clearClosedWindowQ();

    void sendToRMT(PDU *pdu);

    void schedule(DTPTimers* timer, double time =0.0);

//    void handleSDUs(CDAPMessage* cdap);
    void setPDUHeader(PDU* pdu);
    void initGates();
    void delimitFromRMT(DataTransferPDU* pdu);
    bool commonRcvControl(ControlPDU* pdu);
    void sendControlAckPDU();
    void sendEmptyDTPDU();
    void sendAckFlowPDU(unsigned int seqNum = 0, bool seqNumValid = false);
    bool setDRFInPDU(bool override);

    void redrawGUI();
    void addPDUToReassemblyQ(DataTransferPDU* pdu);
    void sendFCOnlyPDU();
    void fillFlowControlPDU(FlowControlPDU* flowControlPdu);
    void sendAckOnlyPDU(unsigned int seqNum);
    void resetSenderInactivTimer();
    void rcvrBufferStateChange();
    bool isDuplicate(unsigned int seqNum);
    void notifyAboutInactivity();
    void notifyAboutUnableMaintain();
    void notifyStopSending();
    void notifyStartSending();

  public:
    DTP();
    virtual ~DTP();

//    bool read(int portId, unsigned char * buffer, int len);
//    bool readImmediate(int portId, unsigned char* buffer, int len);
//    bool write(int portId, unsigned char *buffer, int len);

    void setFlow(Flow* flow);
    void setDTCP(DTCP* dtcp);
    const QoSCube* getQoSCube() const;
    void setQoSCube(const QoSCube* qosCube);
    void setPduDroppingEnabled(bool pduDroppingEnabled);

    void flushAllQueuesAndPrepareToDie();
    cModule* createPolicyModule(const char* prefix, const char* name);
    void startATimer(unsigned int seqNum);

    void runCongestionNotificationPolicy();

  protected:
    virtual void handleMessage(cMessage *msg);
    virtual void initialize(int step);
    int numInitStages() const
    {
      return 2;
    }
    void initSignalsAndListeners();

    ;

    //Signals

    simsignal_t sigEFCPStahpSending;
    simsignal_t sigEFCPStartSending;

    //Statistic signals
    simsignal_t sigStatDTPRTT;
    simsignal_t sigStatDTPClosedWinQ;


};

#endif /* DTP_H_ */
