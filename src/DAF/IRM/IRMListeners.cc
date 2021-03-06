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

#include "IRM.h"
#include "IRMListeners.h"

IRMListeners::IRMListeners(IRM* nirm) {
    this->irm = nirm;
}

IRMListeners::~IRMListeners() {
    irm = NULL;
}

void LisIRMAllocReq::receiveSignal(cComponent* src, simsignal_t id, cObject* obj) {
    EV << "AllocationRequest initiated by " << src->getFullPath()
       << " and processed by " << irm->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);

    if (flow) {
       if (irm->getConTable()->findEntryByFlow(flow))
           irm->receiveAllocationRequestFromAe(flow);
    }
    else
       EV << "IRMListener received unknown object!" << endl;
}

void LisIRMDeallocReq::receiveSignal(cComponent* src, simsignal_t id, cObject* obj) {
    EV << "DeallocationRequest initiated by " << src->getFullPath()
       << " and processed by " << irm->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);

    if (flow) {
       if (irm->getConTable()->findEntryByFlow(flow))
           irm->receiveDeallocationRequestFromAe(flow);
    }
    else
       EV << "IRMListener received unknown object!" << endl;
}
