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

package rina.DAF.AE;

simple AESender extends AE like IAE
{
    parameters:
        @class(AESender);
        string dstApName = default("AppErr");
        string dstApInstance = default("0");
        string dstAeName = default("AeErr");
        string dstAeInstance = default("0");
        
        int startAt @unit(s) = default(0s);
        int stopAt  @unit(s) = default(0s);
        int sendAfter  @unit(s) = default(0s);
        
        double rate = default(1);  
        double ratevar = default(0);    
        
        int size = default(1024);
        int sizevar = default(0);
        
        
        bool printAtEnd = default(false);
        
        @signal[arrivalPong](type="simtime_t");
        @signal[arrivalPong1](type="simtime_t");
        @signal[arrivalPong2](type="simtime_t");
        @signal[arrivalPong3](type="simtime_t");
        @signal[arrivalPong4](type="simtime_t");
        
		@statistic[pongDelay1](title="pong delay"; source="arrivalPong"; record=vector,stats; interpolationmode=none);
		@statistic[pongDelay1](title="pong delay1"; source="arrivalPong1"; record=vector,stats; interpolationmode=none);
		@statistic[pongDelay2](title="pong delay2"; source="arrivalPong2"; record=vector,stats; interpolationmode=none);
		@statistic[pongDelay3](title="pong delay3"; source="arrivalPong3"; record=vector,stats; interpolationmode=none);
		@statistic[pongDelay4](title="pong delay4"; source="arrivalPong4"; record=vector,stats; interpolationmode=none);
        
}
