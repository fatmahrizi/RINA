//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package rina.src.DIF.EFCP.DTCP;

//
// TODO auto-generated type
//
simple DTCP
{
    parameters:
        @display("i=block/subqueue");
        
        string ecnPolicy = default("");
        string rcvrFCPolicy = default("");
        string rcvrAckPolicy = default("");
        string receivingFCPolicy = default("");
        string sendingAckPolicy = default("");
        string lostControlPDUPolicy = default("");
        string rcvrControlAckPolicy = default("");
        string senderAckPolicy = default("");
        string fcOverrunPolicy = default("");
        string noOverridePeakPolicy = default("");
        string txControlPolicy = default("");
        string noRateSlowDownPolicy = default("");
        string reconcileFCPolicy = default("");
        string rateReductionPolicy = default("");
        string ecnSlowDownPolicy = default("");
        
//        @signal[DTCP_CLOSED_WIN_Q](type=double);
//        @statistic[dtcp-rtt](title="Closed-window Queue length"; source=DTCP_CLOSED_WIN_Q; record=vector, mean);
        @signal[DTCP_RX_SENT](type=unsigned long);
        @statistic[dtcp-rx-sent](title="Sum of all retransmissions"; source=DTCP_RX_SENT; record=last);
}
