#pragma once
#include <string>
#include <fstream>
#include <iostream>

enum class PacketTypes {
    CreateProfilePacket,
    EditProfilePacket,
    VotePacket
};

typedef struct Header
{
    PacketTypes packetType;
    int Length;
    int NumOfBytes;
} Head;

class Packet {
     Head header;
     char* dataField;
     unsigned int CRC;
     const unsigned int CONSTCRC = 0xFF00FF00;

public:

     unsigned int CalculateCRC()
     {
         //Set the CRC to 0xFF00FF00
         CRC = CONSTCRC;
         return CRC;

     }

     char* SerializeData()
     {
         CRC = CalculateCRC();

         // Set to the total number of bytes
         header.Length = strlen(dataField);
         int TotalSize = sizeof(Head) + header.Length + sizeof(CRC);
         header.NumOfBytes = TotalSize;
         // Allocate memory to buffer
         char* TxBuffer = new char[TotalSize];

         // Copy the header information
         memcpy(TxBuffer, &header, sizeof(Head));

         // Copy the body
         memcpy(TxBuffer + sizeof(Head), dataField, header.Length);

         // Copy the CRC
         memcpy(TxBuffer + sizeof(Head) + header.NumOfBytes, &CRC, sizeof(CRC));

         // Return refence point to the packet
         return TxBuffer;
     }

     void DeserializeData(char* buffer) {
         if (buffer == nullptr) {
             std::cerr << "Error: Null buffer pointer." << std::endl;
             return;
         }

         // Copy the header information from buffer to header
         memcpy(&header, buffer, sizeof(Head));

         // Allocate memory for dataField based on header.Length
         dataField = new char[header.Length];

         // Copy the body from buffer to dataField
         memcpy(dataField, buffer + sizeof(Head), header.Length);

         // Copy the CRC from buffer to CRC
         memcpy(&CRC, buffer + sizeof(Head) + header.NumOfBytes, sizeof(CRC));
     }

     void setPacketType(PacketTypes type) { header.packetType = type; }

     PacketTypes getPacketType() { return header.packetType; }
};

