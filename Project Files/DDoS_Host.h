#ifndef __FINAL_LAB_H_
#define __FINAL_LAB_H_

#include <omnetpp.h>
#include "Message_m.h"
#include "IP_Manage_m.h"
#include <string>


using namespace omnetpp;


class DDoS_Host : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void send_msg();

  private:
    int ip_suffix;
    int messages = 0;
};

#endif
