//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

#ifndef __RINA_RMTQUEUE_H_
#define __RINA_RMTQUEUE_H_

#include <omnetpp.h>
#include <queue>

#include "RINASignals.h"
#include "PDU.h"
#include "Flow.h"


class RMTQueue : public cSimpleModule
{
  /* tight coupling for management purposes */
  friend class RMT;
  friend class RMTPort;
  friend class RMTModuleAllocator;

  public:

    virtual ~RMTQueue();

    /**
     * Queue type (i.e. its direction).
     */
    enum queueType { INPUT = 'I', OUTPUT = 'O'};

    /**
     * Returns the queue's type (i.e. its direction).
     *
     * @return queue type enum value
     */
    queueType getType() const;

    /**
     * Returns the current length of the message queue.
     *
     * @return length
     */
    int getLength() const;

    /**
     * Returns the timestamp of the simulation time from which the queue has been empty.
     * Usable only if the queue is currently empty.
     *
     * @return start of queue idle time
     */
    simtime_t getQTime() const;

    /**
     * Returns the maximum length of the queue.
     *
     * @return maximum length
     */
    int getMaxLength() const;

    /**
     * Sets the maximum length of the queue.
     *
     * @param value new maximum
     */
    void setMaxLength(int value);

    /**
     * Returns the threshold length of the queue.
     *
     * @return threshold length
     */
    int getThreshLength() const;

    /**
     * Sets the threshold length of the queue.
     *
     * @param value new threshold
     */
    void setThreshLength(int value);
//
//    /**
//     * Returns the queue ID. Its content is determined by RA's QueueIdGen policy.
//     *
//     * @return queue ID
//     */
//    const char* getQueueId() const;
//
//    /**
//     * Sets the queue ID.
//     *
//     * @param queueId new queue ID
//     */
//    void setQueueId(const char* queueId);

    Flow* getFlow() const;
    void setFlow(Flow* _flow);

    /**
     * Returns a pointer to the first PDU in the queue.
     *
     * @return PDU
     */
    const cPacket* getFirstPDU() const;

    /**
     * Returns a pointer to the last PDU in the queue.
     *
     * @return PDU
     */
    const cPacket* getLastPDU() const;

    /**
     * Iterators.
     */
    typedef std::deque<cPacket*>::iterator iterator;
    typedef std::deque<cPacket*>::const_iterator const_iterator;
    iterator begin() { return queue.begin(); }
    iterator end() { return queue.end(); }

    /**
     * Sends out the first PDU in the queue.
     */
    void releasePDU();

    /**
     * Marks the last PDU in a queue with a congestion bit.
     */
    void markCongestionOnLast();

    /**
     * Spews out some information about queue state.
     */
    std::string info() const;

  protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage* msg);

  private:
    std::deque<cPacket*> queue;
    queueType type;

    int maxQLength;
    int thresholdQLength;

    Flow * flow;

    simtime_t qTime;

    cGate* rmtAccessGate;
    cGate* outputGate;
    cGate* inputGate;

    void setType(queueType type);

    void enqueuePDU(cPacket* pdu);
    cPacket* dropLast();

    cGate* getOutputGate() const;
    cGate* getInputGate() const;
    cGate* getRMTAccessGate() const;
    void setRMTAccessGate(cGate* gate);



    void redrawGUI();

    simsignal_t sigRMTPDURcvd;
    simsignal_t sigRMTPDUSent;
    simsignal_t sigStatRMTQueueLength;
};

typedef RMTQueue::queueType RMTQueueType;
typedef std::vector<RMTQueue*>  RMTQueues;
typedef RMTQueues::iterator  RMTQueuesIter;
typedef RMTQueues::const_iterator  RMTQueuesConstIter;

std::ostream& operator<< (std::ostream& os, const RMTQueue& cte);

#endif
