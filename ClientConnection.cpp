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
	Packet packet;
	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer),0);
	if ((bytesReceived) <= 0 ){
		
		return PacketTypes::InvalidPacket;
	
	};
	
	
	packet.DeserializeData(buffer);
	delete[] buffer;
	return packet.getPacketType();

}

void ClientConnection::closeConnection(){
	closesocket(clientSocket);
	WSACleanup();
}


void ClientConnection::sendPacket(Packet &packet){

	char* serializedData = packet.SerializeData();
    int dataSize = packet.getDataSize() + sizeof(PacketTypes);
    send(clientSocket, serializedData, dataSize, 0);
    delete[] serializedData;
}
    
	
	
void ClientConnection::receivePacket(Packet &packet){

	char buffer[sizeof(int)*2];
	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), MSG_PEEK);
	if ((bytesReceived) <= 0 ){
		return;
	};

	int length, numOfBytes;
	memcpy(&length, buffer, sizeof(int));
	memcpy(&numOfBytes, buffer+sizeof(int), sizeof(int));

	int totalSize=numOfBytes;
	char* totalBuffer = new char[totalSize];
	
	int bytesReceived = recv(clientSocket, totalBuffer, totalSize, 0);
	if ((bytesReceived) <= 0 ){
		delete[] totalBuffer;
		return;
	};

	packet.DeserializeData(totalBuffer);
	delete[] totalBuffer;
	
}

    

    