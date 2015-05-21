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

#include <BEMonitor.h>

namespace BEMonitor {

Define_Module(BEMonitor);

void BEMonitor::onPolicyInit(){}

void BEMonitor::postPDUInsertion(RMTQueue* queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] ++;
            inQ[port].push_back(queue);
        }
        if(queue->getType() == RMTQueue::OUTPUT){
            outC[port] ++;
            outQ[port].push_back(queue);
        }
    }
}

void BEMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] --;
            inQ[port].pop_back();
        } else {
            outC[port] --;
            outQ[port].pop_back();
        }
    }
}

void BEMonitor::postQueueCreation(RMTQueue* queue){
}

int BEMonitor::getInCount(RMTPort* port) {
    return inC[port];
}

int BEMonitor::getInThreshold(RMTQueue * queue){
    return queue->getMaxLength();
}

RMTQueue* BEMonitor::getNextInput(RMTPort* port){
    RMTQueue* q = NULL;

    QueuesList* ql = &(inQ[port]);
    if(!ql->empty()) {
        q = ql->front();
        ql->pop_front();
    }

    if(q != NULL){
        inC[port]--;
    }

    return q;
}

int BEMonitor::getOutCount(RMTPort* port){
    return outC[port];
}

int BEMonitor::getOutThreshold(RMTQueue * queue){
    return queue->getMaxLength();
}

RMTQueue* BEMonitor::getNextOutput(RMTPort* port){
    RMTQueue* q = NULL;

    QueuesList* ql = &(outQ[port]);
    if(!ql->empty()) {
        q = ql->front();
        ql->pop_front();
    }

    if(q != NULL){
        outC[port]--;
    }

    return q;
}

queueStat BEMonitor::getInStat(RMTQueue * queue){
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    return queueStat(inC[port],queue->getMaxLength(),1,queue->getMaxLength());
}
queueStat BEMonitor::getOutStat(RMTQueue * queue){
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    return queueStat(outC[port],queue->getMaxLength(),1,queue->getMaxLength());
}



}
