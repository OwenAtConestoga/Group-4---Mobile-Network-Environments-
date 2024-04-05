#pragma once
#include "clientConnection.h"
#include "structDefinitions.h"

#define MAX_PACKET_SIZE 1024

class ReadDataClient {
private:
    ClientConnection& clientConnection;

public:
    ReadDataClient(ClientConnection& connection);
    void receivePacket(Packet& packet);
};
