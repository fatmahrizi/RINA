//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @file DTCPSendingAckPolicyBase.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#ifndef SENDINGACKPOLICYBASE_H_
#define SENDINGACKPOLICYBASE_H_

#include <omnetpp.h>

#include "EFCPPolicy.h"

/*
 *
 */
class SendingAckPolicyBase : public EFCPPolicy
{
  public:
    SendingAckPolicyBase();
    virtual ~SendingAckPolicyBase();
//    virtual bool run(DTPState* dtpState, DTCPState* dtcpState, ATimer* timer) = 0;
    void defaultAction(DTPState* dtpState, DTCPState* dtcpState);

  protected:
    virtual void initialize(){};
    virtual void handleMessage(cMessage* msg){};
};

#endif /* SENDINGACKPOLICYBASE_H_ */
