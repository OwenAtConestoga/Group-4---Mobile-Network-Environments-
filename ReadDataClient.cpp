#include "readDataClient.h"
#include <iostream>

ReadDataClient::ReadDataClient(ClientConnection& connection) : clientConnection(connection) {}

void ReadDataClient::receivePacket(Packet& packet) {
    char buffer[MAX_PACKET_SIZE];
    int bytesReceived = clientConnection.receiveData(buffer, MAX_PACKET_SIZE);

    if (bytesReceived > 0) {
        memcpy(&packet.Head, buffer, sizeof(Header));
        packet.dataField.assign(buffer + sizeof(Header), packet.Head.Length);
        packet.CRC = *reinterpret_cast<unsigned int*>(buffer + sizeof(Header) + packet.Head.Length);
    }
    else {
        packet.Head.packetType = PacketTypes::InvalidPacket;
    }
}
