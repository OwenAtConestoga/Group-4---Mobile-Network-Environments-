#pragma once
#include "serverConnection.h"
#include "createProfile.h"
using namespace std;
#define NUMOFDELIMSPROFILE 4
#define NUMOFDELIMSACCT 1

class SendDataServer
{
public:
    packetClass pktClass;

    SendDataServer(packetClass transmittedPacket)
    {
        memcpy(&pktClass, &transmittedPacket, sizeof(packetClass));
    }

    char* SerializeData()
    {
        int TotalSize;
        // Find Length
        if (pktClass.profile.size() > 8) {
            pktClass.Head.profileLength += NUMOFDELIMSPROFILE;
        }
        else {
            pktClass.Head.profileLength -= 8;
        }
        if (pktClass.loginInfo.size() > 0) {
            pktClass.Head.acctLength += NUMOFDELIMSACCT;
        }
        pktClass.Head.profileLength += pktClass.profile.size();
        pktClass.Head.acctLength += pktClass.loginInfo.size();
        pktClass.CRC = CalculateCRC();

        // Find Total Size
        TotalSize = sizeof(Header) + pktClass.Head.profileLength + pktClass.Head.acctLength + sizeof(const unsigned int) + sizeof(unsigned int);
        pktClass.Head.NumOfBytes = TotalSize;

        char* TxBuffer = new char[128];

        // Offset initialization
        int offset = 0;

        // Packet
        if (TxBuffer) {
            // Copy header
            memcpy(TxBuffer + offset, &pktClass.Head, sizeof(Header));
            offset += sizeof(Header);

            // Copy profile
            if (pktClass.Head.profileLength > 0) {
                memcpy(TxBuffer + offset, static_cast<string>(pktClass.profile).c_str(), pktClass.Head.profileLength);
                offset += pktClass.Head.profileLength;
            }

            // Copy account
            if (pktClass.Head.acctLength > 0) {
                memcpy(TxBuffer + offset, static_cast<string>(pktClass.loginInfo).c_str(), pktClass.Head.acctLength);
                offset += pktClass.Head.acctLength;
            }

            // Copy CRC
            memcpy(TxBuffer + offset, &pktClass.CRC, sizeof(unsigned int));
            offset += sizeof(unsigned int);

            // Copy CONSTCRC
            memcpy(TxBuffer + offset, &pktClass.CONSTCRC, sizeof(unsigned int));
        }

        return TxBuffer;
    }


    unsigned int CalculateCRC() {
        unsigned int crc = 0;  // Initial CRC value
        for (int i = 0; i < pktClass.profile.size(); ++i) {
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
        for (int i = 0; i < pktClass.loginInfo.size(); ++i) {
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