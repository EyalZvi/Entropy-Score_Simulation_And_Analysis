
message Msg extends omnetpp::cPacket	// A very minimal representation of an IP forwarded packet: 
{
    // Src IP for packet sending 
	int src_ip;
	
	// Sending Time - For data collection
	simtime_t sending_time;
	
}