#include "Normal_Host.h"

Define_Module(Normal_Host);

void Normal_Host::initialize()
{
    cMessage *self_msg = new cMessage();
    simtime_t next_event_rand = simTime() + 0.001 + uniform(0,0.001);   // Set next event time and schedule it
    scheduleAt(next_event_rand,self_msg);

}

void Normal_Host::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        if((messages < 9 && this->getIndex() < 9)||(messages < 8 && this->getIndex() >= 9))
        {
        simtime_t next_event_rand = simTime() + uniform(0,0.85);    // Set next event time and schedule it
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

void Normal_Host::send_msg()
{
    Msg* msg_pck = new Msg();
    msg_pck->setSrc_ip(ip_suffix);
    msg_pck->setSending_time(simTime());
    send(msg_pck,"gate$o");
}
