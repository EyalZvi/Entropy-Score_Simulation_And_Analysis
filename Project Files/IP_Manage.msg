
message IP_Manage extends omnetpp::cPacket	// A very minimal representation of an IP forwarded packet: 
{
    // Assign IPs to hosts by host type
	int ip_suffix;
}