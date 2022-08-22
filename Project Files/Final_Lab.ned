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

network Final_Lab
{
    parameters:
        int num_of_n_hosts;
        int num_of_ddos_hosts;
        int num_of_fc_hosts; 

        @display("bgb=10000,10000");
    submodules:

        normal_host[num_of_n_hosts]: Normal_Host {

            @display("i=device/pc;p=6000,500,m,5,750,750");
        }

        ddos_host[num_of_ddos_hosts]: DDoS_Host {

            @display("i=old/telnet;p=500,6500,ri,1500,1500");
        }

        fc_host[num_of_fc_hosts]: Flash_Crowd_Host {

            @display("i=device/lan;p=800,500,m,5,750,750");
        }

        center_point: Center_Point {

            @display("i=device/server2;p=5000,8500");
        }

    connections:
        for i=0..(num_of_n_hosts - 1) {
            normal_host[i].gate <--> center_point.gate[i];
        }
        for i=0..(num_of_ddos_hosts - 1) {
            ddos_host[i].gate <--> center_point.gate[i + num_of_n_hosts];
        }

        for i=0..(num_of_fc_hosts - 1) {
            fc_host[i].gate <--> center_point.gate[i + num_of_n_hosts + num_of_ddos_hosts];
        }

}
