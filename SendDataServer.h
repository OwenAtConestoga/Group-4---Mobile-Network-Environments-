#pragma once
#include "serverConnection.h"
#include "createProfile.h"
using namespace std;

class SendDataServer
{
public:
    packetClass pktClass;

    SendDataServer(packetClass transmittedPacket)
    {
        memcpy(&pktClass, &transmittedPacket, sizeof(packetClass));
    }

    char* SerializeData() {
        int TotalSize;
        // Find Length
        pktClass.Head.profileLength = pktClass.profile.size();
        pktClass.Head.acctLength = pktClass.loginInfo.size();
        pktClass.CRC = CalculateCRC();

        // Find Total Size
        TotalSize = sizeof(Header) + pktClass.Head.profileLength + pktClass.Head.acctLength + sizeof(const unsigned int) + sizeof(unsigned int);
        pktClass.Head.NumOfBytes = TotalSize;

        char* TxBuffer = (char*)calloc(TotalSize, sizeof(char));

        // Packet
        memcpy(TxBuffer, &pktClass.Head, sizeof(Header));

        // Data
        memcpy(TxBuffer + sizeof(Header), &pktClass.profile, pktClass.Head.profileLength);
        memcpy(TxBuffer + sizeof(Header) + pktClass.Head.profileLength, &pktClass.loginInfo, pktClass.Head.acctLength);
        memcpy(TxBuffer + sizeof(Header) + pktClass.Head.profileLength + pktClass.Head.acctLength, &pktClass.CRC, sizeof(unsigned int));
        memcpy(TxBuffer + sizeof(Header) + pktClass.Head.profileLength + pktClass.Head.acctLength + sizeof(unsigned int), &pktClass.CONSTCRC, sizeof(const unsigned int));
        return TxBuffer;
    }

    unsigned int CalculateCRC() {
        unsigned int crc = 0;  // Initial CRC value
        for (int i = 0; i < pktClass.Head.profileLength; ++i) {
            crc ^= static_cast<string>(pktClass.profile)[i];
            for (int j = 0; j < 8; ++j) {
                if (crc & 0x00000001) {
                    crc = (crc >> 1) ^ pktClass.CONSTCRC;
                }
                else {
                    crc >>= 1;
                }
            }
        }
        for (int i = 0; i < pktClass.Head.acctLength; ++i) {
            crc ^= static_cast<string>(pktClass.loginInfo)[i];
            for (int j = 0; j < 8; ++j) {
                if (crc & 0x00000001) {
                    crc = (crc >> 1) ^ pktClass.CONSTCRC;
                }
                else {
                    crc >>= 1;
                }
            }
        }
        return crc;
    }
};