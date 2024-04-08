#pragma once
#include "clientConnection.h"
#include "structDefinitions.h"
#include "packet.h"

class SendDataClient {
private:
    ClientConnection& clientConnection;
    int TotalSize;

public:
    SendDataClient(ClientConnection& connection);
    char* serializeData(packetClass& packet);
    void sendPacket(packetClass& packet);
};
