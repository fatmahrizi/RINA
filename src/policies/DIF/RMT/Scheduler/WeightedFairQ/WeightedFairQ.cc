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

#include <WeightedFairQ/WeightedFairQ.h>

Define_Module(FWQ::WeightedFairQ);

namespace FWQ {

using namespace std;


void WeightedFairQ::onPolicyInit() {
    monitor= check_and_cast<WeightedFairQMonitor*> (getModuleByPath("^.queueMonitorPolicy"));
    if (monitor == NULL) {
        EV << "!!! WeightedFairQMaxQ has to be used in conjecture with WeightedFairQ!" << endl;
    }
}


void WeightedFairQ::processQueues(RMTPort* port, RMTQueueType direction) {
    Enter_Method("processQueues()");

    switch(direction){
        case RMTQueue::INPUT:
            if (port->isInputReady() && port->getWaiting(RMTQueue::INPUT)) {
                port->setInputBusy();
                RMTQueue* inQ = port->getManagementQueue(RMTQueue::INPUT);
                if (inQ->getLength() > 0) {
                    inQ->releasePDU();
                } else {
                    inQ = port->getLongestQueue(RMTQueue::INPUT);
                    inQ->releasePDU();
                }
            }
        break;
        case RMTQueue::OUTPUT:
            if (port->isOutputReady() && port->getWaiting(RMTQueue::OUTPUT)) {
                port->setOutputBusy();
                RMTQueue* outQ = port->getManagementQueue(RMTQueue::OUTPUT);
                if (outQ->getLength() > 0) {
                    outQ->releasePDU();
                } else {
                    outQ =  monitor->getNextQueue();
                    if(outQ && outQ->getLength() > 0) {
                        outQ->releasePDU();
                    } else {
                        port->setOutputReady();
                    }
                }
            }
            break;
    }
}

} /* namespace FWQ */

