package rina.examples.TreeCongestion;
import ned.DatarateChannel;
import rina.CS.Host1AP;
import rina.CS.InteriorRouterMInt;

network TreeCongestion {
	submodules:
		C : InteriorRouterMInt;
		Q : InteriorRouterMInt;
		T0 : InteriorRouterMInt;
		S0_0 : Host1AP;
		R0_0 : Host1AP;
		S0_1 : Host1AP;
		R0_1 : Host1AP;
		S0_2 : Host1AP;
		R0_2 : Host1AP;
		S0_3 : Host1AP;
		R0_3 : Host1AP;
	connections:
		C.medium++ <--> DatarateChannel {  datarate = 2909kbps; delay = 1ms; } <--> Q.medium++;
		T0.medium++ <--> DatarateChannel {  datarate = 3200kbps; delay = 1ms; } <--> C.medium++;
		S0_0.medium <--> T0.medium++;
		R0_0.medium <--> Q.medium++;
		S0_1.medium <--> T0.medium++;
		R0_1.medium <--> Q.medium++;
		S0_2.medium <--> T0.medium++;
		R0_2.medium <--> Q.medium++;
		S0_3.medium <--> T0.medium++;
		R0_3.medium <--> Q.medium++;
}
