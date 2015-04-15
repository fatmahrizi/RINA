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

#include "DL.h"

Define_Module(DL);

void DL::onPolicyInit()
{
    monitor= check_and_cast<DLMonitor*>
        (getModuleByPath("^.queueMonitorPolicy"));
    if (monitor == NULL)
    {
        EV << "!!! DLMaxQ has to be used in conjecture with DLMonitor!" << endl;
    }
}


void DL::processQueues(RMTPort* port, RMTQueueType direction)
{
    Enter_Method("processQueues()");
    switch(direction){
        case RMTQueue::OUTPUT:
            if (port->isOutputReady() && port->getWaiting(RMTQueue::OUTPUT)) {
                port->setOutputBusy();
                RMTQueue* outQ = port->getManagementQueue(RMTQueue::OUTPUT);
                if (outQ->getLength() > 0) {
                    outQ->releasePDU();
                } else {
                    outQ =  monitor->getNextUrgentQ(port);
                    if(outQ && outQ->getLength() > 0) {
                        outQ->releasePDU();
                    } else {
                        port->setOutputReady();
                    }
                }
            }
            break;
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
    }
}
