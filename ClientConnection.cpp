// Client Connection Class
// Matteo Filippone

#include "ClientConnection.h"
#include "header.h"

bool ClientConnection::connectToServer(){
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return false;
	}

	//initializes socket. SOCK_STREAM: TCP
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return false;
	}

    return true;

}


void ClientConnection::sendLoginRequest(const char* username, const char* password) {
    std::string credentials = std::string(username) + "," + std::string(password);

    Packet packet;
    packet.setPacketType(PacketTypes::LoginRequestPacket);
    packet.setData(const_cast<char*>(credentials.c_str()));

    char* serializedData = packet.SerializeData();
    int dataSize = packet.getDataSize() + sizeof(PacketTypes);
    send(clientSocket, serializedData, dataSize, 0);
    delete[] serializedData;
}

PacketTypes ClientConnection::receiveLoginResponse(){
	char buffer[1024];
	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer),0);
	if ((bytesReceived) <= 0 ){
		
		return PacketTypes::InvalidPacket;
	
	};
	
	Packet packet;
	packet.DeserializeData(buffer);
	return packet.getPacketType();

}

void ClientConnection::closeConnection(){
	closesocket(clientSocket);
	WSACleanup();
}



    

    