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

package rina.examples.TwoCSsSimple;

import ned.DatarateChannel;
import rina.src.CS.TestHost1AP;


network TwoCSsSimple
{
    @display("bgb=325,196");
    submodules:
        host1: TestHost1AP {
            @display("p=82,92");
        }
        host2: TestHost1AP {
            @display("p=231,92");
        }
    connections allowunconnected:
//        host1.medium <--> host2.medium;
        host1.medium <--> DatarateChannel {delay = 0.4s; ber = 0; datarate = 10Mbps; } <--> host2.medium;
}
