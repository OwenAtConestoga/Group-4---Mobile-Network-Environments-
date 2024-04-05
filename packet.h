#pragma once
#include "structDefinitions.h"

class packetClass
{
public:
	Packet pkt;
	Profile profile;
	Account loginInfo;

	packetClass()
	{
		pkt.Head.NumOfBytes = 0;
		pkt.Head.acctLength = 0;
		pkt.Head.packetType = PacketTypes::InvalidPacket;
		pkt.Head.profileLength = 0;
		profile;
		loginInfo;
	}
};