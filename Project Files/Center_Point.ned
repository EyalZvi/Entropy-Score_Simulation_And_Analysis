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

//
// TODO auto-generated module
//
simple Center_Point
{
    parameters:
        int num_of_n_hosts;
		int num_of_ddos_hosts;
		int num_of_fc_hosts;

    	@signal[Entropy*](type=float);
		@statisticTemplate[Entropy](record=vector,stats; interpolationmode=none);
		
		@signal[Probability*](type=float);
		@statisticTemplate[Probability](record=vector,stats; interpolationmode=none);
		
		@signal[Score*](type=float);
		@statisticTemplate[Score](record=vector,stats; interpolationmode=none);
		
    gates:
        inout gate[num_of_n_hosts + num_of_ddos_hosts + num_of_fc_hosts];
}
