#include "DDoS_Host.h"

Define_Module(DDoS_Host);

void DDoS_Host::initialize()
{
    cMessage *self_msg = new cMessage();
    simtime_t next_event_rand = simTime() + 5 + uniform(0,0.001);    // Set next event time and schedule it
    scheduleAt(next_event_rand,self_msg);
}

void DDoS_Host::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        if((messages < 54 && this->getIndex() < 14)||(messages < 53 && this->getIndex() == 14))
        {
        simtime_t next_event_rand = simTime() + uniform(0,0.18);   // Set next event time and schedule it
        scheduleAt(next_event_rand,msg);
        send_msg();
        messages ++;
        }
        else delete msg;
    }
    else
    {
        IP_Manage* assigned_ip = check_and_cast<IP_Manage*>(msg);
        ip_suffix = assigned_ip->getIp_suffix();
        delete assigned_ip;
    }
}

void DDoS_Host::send_msg()
{
    Msg* msg_pck = new Msg();
    msg_pck->setSrc_ip(ip_suffix);
    msg_pck->setSending_time(simTime());
    send(msg_pck,"gate$o");
}
