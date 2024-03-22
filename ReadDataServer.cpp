#include "ReadDataServer.h"

ReadDataServer::ReadDataServer(string RX, int& Size, Profile newProfile, Packet newPkt)
{
    RxBuffer = RX;
    TotalSize = Size;
    profile = newProfile;
    pkt.CRC = newPkt.CRC;
    pkt.dataField = newPkt.dataField;
    pkt.Head = newPkt.Head;
}

void ReadDataServer::DeserializeData(char* buffer) {
    if (buffer == NULL) {
        std::cerr << "Error: Null buffer pointer." << std::endl;
        return;
    }

    // Copy the header information from buffer to header
    memcpy(&pkt.Head, buffer, sizeof(Header));

    // Allocate memory for dataField based on header.Length
    pkt.dataField = new char[pkt.Head.Length];

    // Copy the body from buffer to dataField
    memcpy(&pkt.dataField, buffer + sizeof(Header), pkt.Head.Length);

    // Copy the CRC from buffer to CRC
    memcpy(&pkt.CRC, buffer + sizeof(Header) + pkt.Head.NumOfBytes, sizeof(pkt.CRC));
}