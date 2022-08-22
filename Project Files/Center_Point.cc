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

#include "Center_Point.h"
#include <cmath>

Define_Module(Center_Point);

void Center_Point::initialize()
{
    int num_of_hosts[3] = {par("num_of_n_hosts"),par("num_of_ddos_hosts"),par("num_of_fc_hosts")};
    for(int i=0; i<edge; i++) ip_suffix[i] = false;

    int rand;
    int num_of_curr_host = 0;

    for(int type=0; type<3; type++)
    {
        for(int i=0; i<num_of_hosts[type]; i++)
        {
            do
            {
                if(type == 0) rand = intuniform(0,choose_edge[type]);
                else rand = intuniform(choose_edge[type-1] + distance + 1,choose_edge[type]);

            }
            while(ip_suffix[rand]);

            ip_suffix[rand] = true;
            send_ip(num_of_curr_host,rand);
            num_of_curr_host ++;
        }
    }

    char signalName[32];
    simsignal_t signal;
    cProperty *statisticTemplate;

        sprintf(signalName, "Entropy");
        signal = registerSignal(signalName);
        statisticTemplate = getProperties()->get("statisticTemplate", "Entropy");
        getEnvir()->addResultRecorders(this, signal, signalName,  statisticTemplate);
        entropy_samp = signal;


    for (int i = 0; i < 3; i++)
    {
        sum_entropy[i] = 0;
        probability_samp[i] = signal;
        score_samp[i] = signal;

        sprintf(signalName, "Probability%d",i);
        signal = registerSignal(signalName);
        statisticTemplate = getProperties()->get("statisticTemplate", "Probability");
        getEnvir()->addResultRecorders(this, signal, signalName,  statisticTemplate);


        sprintf(signalName, "Score%d");
        signal = registerSignal(signalName);
        statisticTemplate = getProperties()->get("statisticTemplate", "Score");
        getEnvir()->addResultRecorders(this, signal, signalName,  statisticTemplate);


        for (int j = 0; j < 47; j++)
        {
            sum_prob[i][j] = 0;
            sum_score[i][j] = 0;

        }

    }

}

void Center_Point::handleMessage(cMessage *msg)
{
    Msg* received = check_and_cast<Msg*>(msg);
    int src_ip = received->getSrc_ip();
    float entropy;
    count_msgs ++;
    std::map<int,Group>::iterator group = assign_to_group(src_ip);
    entropy = system_entropy();

    ///////////////////////////////////////////////////////////////////
    //Collecting data

    int active_g = active_groups();
    std::map<int,Group>::iterator iter;
    float prob_calc = 0;
    float score_calc = 0;

    if((groups_added < active_g && groups_added > 0) ||(groups_added == 47 && simTime() > 32))
    {
        emit(entropy_samp,sum_entropy[groups_added - 1] /count_entropy);
        count_entropy = 0;

        if(groups_added > 0 && groups_added <6)
        {
            emit(probability_samp[0], sum_prob[0][groups_added - 1] / count_curr_prob);
            emit(score_samp[0], sum_score[0][groups_added - 1] / count_curr_score);
        }

        if(groups_added == 6 || groups_added == 7)
        {
            emit(probability_samp[1], sum_prob[0][groups_added - 1] / count_curr_prob);
            emit(score_samp[1], sum_score[0][groups_added - 1] / count_curr_score);
        }

        if(groups_added > 7)
        {
            emit(probability_samp[2], sum_prob[0][groups_added - 1] / count_curr_prob);
            emit(score_samp[2], sum_score[0][groups_added - 1] / count_curr_score);
        }

        count_curr_prob = 0;
        count_curr_score = 0;
    }
    groups_added = active_g;

    sum_entropy[groups_added - 1]  += entropy;
    count_entropy++ ;

    for(int k=0 ; k<edge ; k++)
    {
        iter = groups.find(k);
        if(iter != groups.end())
        {
            prob_calc += iter->second.curr_prob / groups_added ;
            score_calc += iter->second.score / groups_added;
        }
    }

    if(groups_added > 0 && groups_added <6)
    {
        sum_prob[0][groups_added - 1] += prob_calc;
        count_curr_prob++ ;
        sum_score[0][groups_added - 1] += score_calc;
        count_curr_score++ ;
    }

    if(groups_added == 6 || groups_added == 7)
    {
        sum_prob[1][groups_added - 1] += prob_calc;
        count_curr_prob++ ;
        sum_score[1][groups_added - 1] += score_calc;
        count_curr_score++ ;
    }

    if(groups_added > 7)
    {
        sum_prob[2][groups_added - 1] += prob_calc;
        count_curr_prob++ ;
        sum_score[2][groups_added - 1] += score_calc;
        count_curr_score++ ;
    }



    ///////////////////////////////////////////////////////////////////

    EV << "Groups in play: " << active_groups() << "\n\n";
    EV << "System Entropy: " << entropy << "\n";
    if(entropy < Th) update_scores();
    else
    {
        group->second.score = float(group->second.curr_prob)/float(group->second.old_prob);
        EV << "Group " << group->first << " score: " << group->second.score << "\n";
        if(group->second.score < T)
        {
            EV << "Flash crowd detected, packets in group " << group->first << " are legitimate\n";
        }
        else
        {
            EV << "DDoS attack detected, packets in group " << group->first << " are malicious\n";

        }
    }

    delete msg;
}

void Center_Point::send_ip(int gate_num, int ip)
{
    IP_Manage* ip_pck = new IP_Manage();
    ip_pck->setIp_suffix(ip);
    send(ip_pck,"gate$o",gate_num);
}


float Center_Point::system_entropy()
{
    float entropy = 0;
    std::map<int,Group>::iterator iter;

    for(int i=0; i<edge; i++)
    {
        iter = groups.find(i);
        if(iter != groups.end())
        {
            entropy -= float(iter->second.curr_prob * log2(iter->second.curr_prob));
        }
    }
    return entropy;
}

int Center_Point::active_groups()
{
    int count = 0;
    for(int i=0; i<edge; i++)
    {
        if(groups.count(i)) count++;
    }
    return count;
}

std::map<int,Group>::iterator Center_Point::assign_to_group(int src_ip)
{
    std::map<int,Group>::iterator iter;
    std::map<int,Group>::iterator res;
    int start,finish;
    float old_prob;

    if(src_ip - distance < 0) start = 0;
    else start = src_ip - distance;
    if(src_ip + distance > edge) finish = edge;
    else finish = src_ip + distance;
    int min_dist = distance + 1;

    for(int i = start; i <= finish ; i++ )
    {
        iter = groups.find(i);
        if(iter != groups.end())
        {
            if(min_dist > abs(iter->first - src_ip))
            {
                min_dist = abs(iter->first - src_ip);
                res = iter;
            }
        }
    }
    if(min_dist < distance + 1)
    {
        res->second.count ++;
        res->second.curr_prob =  float(res->second.count)/count_msgs;
    }
    else
    {
        EV << "Group "  << src_ip << " was formed \n";
        Group new_group;
        new_group.count = 1;
        new_group.curr_prob = 1.0/float(count_msgs);
        new_group.old_prob = stored_prob;
        new_group.score = float(new_group.curr_prob)/float(new_group.old_prob);
        groups.insert(std::pair<int,Group>(src_ip,new_group));
        res = groups.find(src_ip);
    }
    return res;
}

void Center_Point::update_scores()
{
    std::map<int,Group>::iterator iter;
    for(int i = 0; i < edge ; i++ )
    {
        iter = groups.find(i);
        if(iter != groups.end())
        {
            iter->second.score = float(iter->second.curr_prob)/float(iter->second.old_prob);
            iter->second.old_prob = iter->second.curr_prob;

        }
    }
}
