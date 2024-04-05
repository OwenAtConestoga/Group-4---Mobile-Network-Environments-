#pragma once
#include "clientConnection.h"
#include "structDefinitions.h"

class SendDataClient {
private:
    ClientConnection& clientConnection;
    int& TotalSize;

public:
    SendDataClient(ClientConnection& connection);
    char* serializeData(const Packet& packet);
    void sendPacket(const Packet& packet);
};
