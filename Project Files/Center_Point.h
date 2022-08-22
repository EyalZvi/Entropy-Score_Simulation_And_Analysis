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

#ifndef __FINAL_LAB_H_
#define __FINAL_LAB_H_

#include <omnetpp.h>
#include "Message_m.h"
#include "IP_Manage_m.h"
#include "Groups.h"
#include <string>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Center_Point : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void send_ip(int gate_num, int ip);
    float system_entropy();
    int active_groups();
    std::map<int,Group>::iterator assign_to_group(int src_ip);
    void update_scores();


  public:
    std::map<int,Group> groups;
  private:
    int f = 64;
    int s = 100;
    int edge = 65536;
    float Th = 2.28;
    float T = 14.9;
    int choose_edge[3] = {f,s,edge};
    float stored_prob = 0.01;
    int distance = 10;
    int count_msgs = 0;
    bool ip_suffix[65536];

    // collecting data
    simsignal_t entropy_samp;
    simsignal_t probability_samp[3];
    simsignal_t score_samp[3];

    float sum_entropy[47];
    int count_entropy;
    float sum_prob[3][47];
    int count_curr_prob = 0;
    float sum_score[3][47];
    int count_curr_score = 0;
    int groups_added = 0;
    //

};

#endif
