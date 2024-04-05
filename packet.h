#pragma once
#include "structDefinitions.h"

class packetClass
{
public:
	Header Head;
	Profile profile;
	Account loginInfo;
	unsigned int CRC;
	const unsigned int CONSTCRC = 0xFF00FF00;
	packetClass()
	{
		Head.NumOfBytes = 0;
		Head.acctLength = 0;
		Head.packetType = PacketTypes::InvalidPacket;
		Head.profileLength = 0;
		profile;
		loginInfo;
		CRC = 0;
	}
};