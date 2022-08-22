//
// Generated file, do not edit! Created by nedtool 5.6 from IP_Manage.msg.
//

#ifndef __IP_MANAGE_M_H
#define __IP_MANAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>IP_Manage.msg:3</tt> by nedtool.
 * <pre>
 * message IP_Manage extends omnetpp::cPacket	// A very minimal representation of an IP forwarded packet: 
 * {
 *     // Assign IPs to hosts by host type
 *     int ip_suffix;
 * }
 * </pre>
 */
class IP_Manage : public ::omnetpp::cPacket
{
  protected:
    int ip_suffix;

  private:
    void copy(const IP_Manage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const IP_Manage&);

  public:
    IP_Manage(const char *name=nullptr, short kind=0);
    IP_Manage(const IP_Manage& other);
    virtual ~IP_Manage();
    IP_Manage& operator=(const IP_Manage& other);
    virtual IP_Manage *dup() const override {return new IP_Manage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getIp_suffix() const;
    virtual void setIp_suffix(int ip_suffix);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const IP_Manage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, IP_Manage& obj) {obj.parsimUnpack(b);}


#endif // ifndef __IP_MANAGE_M_H

