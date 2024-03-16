#pragma once
#include <string>
#include <fstream>
#include <iostream>

enum class PacketTypes {
    CreateProfilePacket,
    EditProfilePacket,
    VotePacket,
    ProfileRequestPacket,
    LoginRequestPacket,
    NoAccessPacket,
    LoginSuccessPacket,
    InvalidPacket,
};

class Packet {
    struct Header
    {
        PacketTypes packetType;
        int Length;
        int NumOfBytes;
    } Head;

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
         Head.Length = strlen(dataField);
         int TotalSize = sizeof(Header) + Head.Length + sizeof(CRC);
         Head.NumOfBytes = TotalSize;
         // Allocate memory to buffer
         char* TxBuffer = new char[TotalSize];

         // Copy the header information
         memcpy(TxBuffer, &Head, sizeof(Header));

         // Copy the body
         memcpy(TxBuffer + sizeof(Header), dataField, Head.Length);

         // Copy the CRC
         memcpy(TxBuffer + sizeof(Header) + Head.NumOfBytes, &CRC, sizeof(CRC));

         // Return refence point to the packet
         return TxBuffer;
     }

     void DeserializeData(char* buffer) {
         if (buffer == nullptr) {
             std::cerr << "Error: Null buffer pointer." << std::endl;
             return;
         }

         // Copy the header information from buffer to header
         memcpy(&Head, buffer, sizeof(Header));

         // Allocate memory for dataField based on header.Length
         dataField = new char[Head.Length];

         // Copy the body from buffer to dataField
         memcpy(dataField, buffer + sizeof(Header), Head.Length);

         // Copy the CRC from buffer to CRC
         memcpy(&CRC, buffer + sizeof(Header) + Head.NumOfBytes, sizeof(CRC));
     }

     void setPacketType(PacketTypes type) { Head.packetType = type; }

     PacketTypes getPacketType() { return Head.packetType; }
     char* getData() { return dataField; }
     void setData(char* newData) { dataField = newData; }

     int getDataSize() const{
        return dataField?strlen(dataField):0;
    }
};

