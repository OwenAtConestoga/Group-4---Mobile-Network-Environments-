#pragma once
#include "serverConnection.h"
#include "createProfile.h"
#include "structDefinitions.h"
using namespace std;

class SendDataServer
{
	string RxBuffer;
	int& TotalSize;
    Packet pkt;
	int ID;

public:
    char* SerializeData()
    {
        // Set to the total number of bytes
        pkt.Head.Length = pkt.dataField.length();
        pkt.CRC = CalculateCRC();

        int TotalSize = sizeof(Header) + pkt.Head.Length + sizeof(pkt.CRC);
        pkt.Head.NumOfBytes = TotalSize;
        // Allocate memory to buffer
        char* TxBuffer = new char[TotalSize];

        // Copy the header information
        memcpy(TxBuffer, &pkt.Head, sizeof(Header));

        // Copy the body
        memcpy(TxBuffer + sizeof(Header), &pkt.dataField, pkt.Head.Length);

        // Copy the CRC
        memcpy(TxBuffer + sizeof(Header) + pkt.Head.NumOfBytes, &pkt.CRC, sizeof(pkt.CRC));

        // Return refence point to the packet
        return TxBuffer;
    }

    unsigned int CalculateCRC() {
        unsigned int crc = 0;  // Initial CRC value
        for (int i = 0; i < pkt.Head.Length; ++i) {
            crc ^= pkt.dataField[i];
            for (int j = 0; j < 8; ++j) {
                if (crc & 0x00000001) {
                    crc = (crc >> 1) ^ pkt.CONSTCRC;
                }
                else {
                    crc >>= 1;
                }
            }
        }
        return crc;
    }
};