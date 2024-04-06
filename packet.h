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
		CRC = 0;
	}
	packetClass& operator=(const packetClass& other)
	{
		if (this != &other) // Check for self-assignment
		{
			Head = other.Head;
			profile = other.profile;
			loginInfo = other.loginInfo;
			CRC = other.CRC;
		}
		return *this;
	}
};