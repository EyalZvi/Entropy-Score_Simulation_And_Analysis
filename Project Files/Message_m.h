//
// Generated file, do not edit! Created by nedtool 5.6 from Message.msg.
//

#ifndef __MESSAGE_M_H
#define __MESSAGE_M_H

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
 * Class generated from <tt>Message.msg:3</tt> by nedtool.
 * <pre>
 * message Msg extends omnetpp::cPacket	// A very minimal representation of an IP forwarded packet: 
 * {
 *     // Src IP for packet sending 
 *     int src_ip;
 * 
 *     // Sending Time - For data collection
 *     simtime_t sending_time;
 * 
 * }
 * </pre>
 */
class Msg : public ::omnetpp::cPacket
{
  protected:
    int src_ip;
    ::omnetpp::simtime_t sending_time;

  private:
    void copy(const Msg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Msg&);

  public:
    Msg(const char *name=nullptr, short kind=0);
    Msg(const Msg& other);
    virtual ~Msg();
    Msg& operator=(const Msg& other);
    virtual Msg *dup() const override {return new Msg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getSrc_ip() const;
    virtual void setSrc_ip(int src_ip);
    virtual ::omnetpp::simtime_t getSending_time() const;
    virtual void setSending_time(::omnetpp::simtime_t sending_time);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Msg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Msg& obj) {obj.parsimUnpack(b);}


#endif // ifndef __MESSAGE_M_H
