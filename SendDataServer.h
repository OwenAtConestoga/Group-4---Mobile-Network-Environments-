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
        pktClass.pkt.Head.profileLength = pktClass.profile.size();
        pktClass.pkt.Head.acctLength = pktClass.loginInfo.size();
        pktClass.pkt.CRC = CalculateCRC();

        // Find Total Size
        TotalSize = sizeof(Packet) + pktClass.pkt.Head.profileLength + pktClass.pkt.Head.acctLength;
        pktClass.pkt.Head.NumOfBytes = TotalSize;

        char* TxBuffer = (char*)calloc(TotalSize, sizeof(char));

        // Packet
        memcpy(TxBuffer, &pktClass.pkt, sizeof(Packet));

        // Data
        memcpy(TxBuffer + sizeof(Packet), &pktClass.profile, pktClass.pkt.Head.profileLength);
        memcpy(TxBuffer + sizeof(Packet) + pktClass.pkt.Head.profileLength, &pktClass.loginInfo, pktClass.pkt.Head.acctLength);

        return TxBuffer;
    }

    unsigned int CalculateCRC() {
        unsigned int crc = 0;  // Initial CRC value
        for (int i = 0; i < pktClass.pkt.Head.profileLength; ++i) {
            crc ^= static_cast<string>(pktClass.profile)[i];
            for (int j = 0; j < 8; ++j) {
                if (crc & 0x00000001) {
                    crc = (crc >> 1) ^ pktClass.pkt.CONSTCRC;
                }
                else {
                    crc >>= 1;
                }
            }
        }
        for (int i = 0; i < pktClass.pkt.Head.acctLength; ++i) {
            crc ^= static_cast<string>(pktClass.loginInfo)[i];
            for (int j = 0; j < 8; ++j) {
                if (crc & 0x00000001) {
                    crc = (crc >> 1) ^ pktClass.pkt.CONSTCRC;
                }
                else {
                    crc >>= 1;
                }
            }
        }
        return crc;
    }
};