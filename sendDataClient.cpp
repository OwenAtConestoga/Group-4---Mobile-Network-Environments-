#include "sendDataClient.h"

SendDataClient::SendDataClient(ClientConnection& connection) : clientConnection(connection), totalSize(0) {}

char* SendDataClient::serializeData(const Packet& packet) {
totalSize = sizeof(Header) + packet.Head.Length + sizeof(packet.CRC);
char* txBuffer = new char[totalSize];

// Header
memcpy(txBuffer, &packet.Head, sizeof(Header));

// Data
memcpy(txBuffer + sizeof(Header), packet.dataField.c_str(), packet.Head.Length);

// CRC
memcpy(txBuffer + sizeof(Header) + packet.Head.Length, &packet.CRC, sizeof(packet.CRC));

return txBuffer;
}

void SendDataClient::sendPacket(const Packet& packet) {
char* txBuffer = serializeData(packet);
int sentBytes = clientConnection.sendData(txBuffer, totalSize);
if (sentBytes != totalSize) {
// Handle error or incomplete send
}
delete[] txBuffer;
}
