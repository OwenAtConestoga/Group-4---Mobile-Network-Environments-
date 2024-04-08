#include "sendDataClient.h"
#define NUMOFDELIMSPROFILE 4
#define NUMOFDELIMSACCT 1

SendDataClient::SendDataClient(ClientConnection& connection) : clientConnection(connection), TotalSize(0) {}

char* SendDataClient::serializeData(packetClass& packet) {
    int TotalSize;
    // Find Length
    if (packet.profile.size() > 8) {
        packet.Head.profileLength += NUMOFDELIMSPROFILE;
    }
    else if (packet.profile.id == 0) {
        packet.Head.profileLength -= 8;
    }

    if (packet.loginInfo.size() > 0) {
        packet.Head.acctLength += NUMOFDELIMSACCT;
    }
    packet.Head.profileLength += packet.profile.size();
    packet.Head.acctLength += packet.loginInfo.size();
    packet.CRC = packet.CONSTCRC;
    TotalSize = sizeof(Header) + packet.Head.profileLength + packet.Head.acctLength + sizeof(const unsigned int) + sizeof(unsigned int);
    packet.Head.NumOfBytes = TotalSize;

    char* TxBuffer = new char[128];

    if (TxBuffer) {
        memcpy(TxBuffer, &packet.Head, sizeof(Header));

        if (packet.Head.profileLength > 0) {
            memcpy(TxBuffer + sizeof(Header), static_cast<string>(packet.profile).c_str(), packet.Head.profileLength);
        }

        if (packet.Head.acctLength > 0) {
            memcpy(TxBuffer + sizeof(Header), static_cast<string>(packet.loginInfo).c_str(), packet.Head.acctLength);
        }

        memcpy(TxBuffer + sizeof(Header) + packet.Head.profileLength + packet.Head.acctLength, &packet.CRC, sizeof(unsigned int));
        memcpy(TxBuffer + sizeof(Header) + packet.Head.profileLength + packet.Head.acctLength + sizeof(unsigned int), &packet.CONSTCRC, sizeof(unsigned int));
    }

    return TxBuffer;
}

void SendDataClient::sendPacket(packetClass& packet) {
    cout << "Hello" << endl;
    char* txBuffer = serializeData(packet);
    int sentBytes = clientConnection.sendData(txBuffer, packet.Head.NumOfBytes);
    if (sentBytes != TotalSize) {
        // Handle error or incomplete send
    }
    
    cout << sentBytes << endl;
    delete[] txBuffer;
}