#include "readDataClient.h"
#include <iostream>

ReadDataClient::ReadDataClient(ClientConnection& connection) : clientConnection(connection) {}

void ReadDataClient::receivePacket(packetClass& packet) {
    char buffer[MAX_PACKET_SIZE];
    int bytesReceived = clientConnection.receiveData(buffer, MAX_PACKET_SIZE);

    if (bytesReceived > 0) {
        memcpy(&packet.Head, buffer, sizeof(Header));
        if (packet.Head.profileLength > 0) {
            packet.profile = Profile(std::string(buffer + sizeof(Header), packet.Head.profileLength));
        }
        if (packet.Head.acctLength > 0) {
            packet.loginInfo = Account(std::string(buffer + sizeof(Header) + packet.Head.profileLength, packet.Head.acctLength));
        }
        packet.CRC = *reinterpret_cast<unsigned int*>(buffer + sizeof(Header) + packet.Head.profileLength + packet.Head.acctLength);
    }
    else {
        packet.Head.packetType = PacketTypes::InvalidPacket;
    }
}