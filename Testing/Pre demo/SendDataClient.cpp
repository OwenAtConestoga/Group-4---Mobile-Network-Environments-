#include "sendDataClient.h"

SendDataClient::SendDataClient(ClientConnection& connection) : clientConnection(connection), TotalSize(0) {}

char* SendDataClient::serializeData(const packetClass& packet) {
    int profileSize = static_cast<int>(packet.profile.userName.length() + packet.profile.firstName.length() + packet.profile.lastName.length() +
        packet.profile.bio.length() + packet.profile.userClass.length() + (2 * sizeof(int)));
    int accountSize = static_cast<int>(packet.loginInfo.username.length() + packet.loginInfo.password.length());
    TotalSize = sizeof(Header) + profileSize + accountSize + sizeof(packet.CRC);
    char* txBuffer = new char[TotalSize];

    // Header
    memcpy(txBuffer, &packet.Head, sizeof(Header));

    // Profile
    int profileOffset = sizeof(Header);
    memcpy(txBuffer + profileOffset, packet.profile.userName.c_str(), packet.profile.userName.length());
    memcpy(txBuffer + profileOffset + packet.profile.userName.length(), packet.profile.firstName.c_str(), packet.profile.firstName.length());
    memcpy(txBuffer + profileOffset + packet.profile.userName.length() + packet.profile.firstName.length(), packet.profile.lastName.c_str(), packet.profile.lastName.length());
    memcpy(txBuffer + profileOffset + packet.profile.userName.length() + packet.profile.firstName.length() + packet.profile.lastName.length(), packet.profile.bio.c_str(), packet.profile.bio.length());
    memcpy(txBuffer + profileOffset + packet.profile.userName.length() + packet.profile.firstName.length() + packet.profile.lastName.length() + packet.profile.bio.length(), packet.profile.userClass.c_str(), packet.profile.userClass.length());
    memcpy(txBuffer + profileOffset + packet.profile.userName.length() + packet.profile.firstName.length() + packet.profile.lastName.length() + packet.profile.bio.length() + packet.profile.userClass.length(), &packet.profile.id, sizeof(int));
    memcpy(txBuffer + profileOffset + packet.profile.userName.length() + packet.profile.firstName.length() + packet.profile.lastName.length() + packet.profile.bio.length() + packet.profile.userClass.length() + sizeof(int), &packet.profile.voteCount, sizeof(int));

    // Account
    int accountOffset = profileOffset + profileSize;
    memcpy(txBuffer + accountOffset, packet.loginInfo.username.c_str(), packet.loginInfo.username.length());
    memcpy(txBuffer + accountOffset + packet.loginInfo.username.length(), packet.loginInfo.password.c_str(), packet.loginInfo.password.length());

    // CRC
    int crcOffset = accountOffset + accountSize;
    memcpy(txBuffer + crcOffset, &packet.CRC, sizeof(packet.CRC));

    return txBuffer;
}

void SendDataClient::sendPacket(const packetClass& packet) {
    cout << "Hello" << endl;
    char* txBuffer = serializeData(packet);
    int sentBytes = clientConnection.sendData(txBuffer, TotalSize);
    if (sentBytes != TotalSize) {
        // Handle error or incomplete send
    }
    
    cout << sentBytes << endl;
    delete[] txBuffer;
}