#include "serverConnection.h"
#include <string>

ServerConnection::ServerConnection()
{
	RxBuffer = (char*)calloc(1, sizeof(Packet) + pkt.Head.Length);
	TxBuffer = (char*)calloc(1, sizeof(Packet) + pkt.Head.Length);
	SDS = (SendDataServer*)calloc(1, sizeof(Packet) + pkt.Head.Length + sizeof(int));
	RDS = (ReadDataServer*)calloc(1, sizeof(Packet) + pkt.Head.Length + sizeof(int) + sizeof(Password) + sizeof(LogOutServer));
}

int ServerConnection::socketCreateBind()
{
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = INADDR_ANY;
	SvrAddr.sin_port = htons(27000);

	if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	{
		socketCleanUp(ServerSocket);
		WSACleanup();
		return -1; // Indicating an error occurred
	}
	return 0; // Indicating success.
}

void ServerConnection::socketCleanUp(SOCKET socket)
{
	closesocket(socket);
}

int ServerConnection::socketListenConnect()
{
	if (listen(ServerSocket, 1) == SOCKET_ERROR)
	{
		socketCleanUp(ServerSocket);
		WSACleanup();
		return -1; // Indicating an error occurred
	}
	return 0; // Indicating success
}

int ServerConnection::recvMsg()
{
	int bytes = recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
	RDS->DeserializeData(RxBuffer);
	return bytes;
}

void ServerConnection::sendMsg()
{
	int size = sizeof(TxBuffer);
	SDS = new SendDataServer(size, TxBuffer);
	send(ConnectionSocket, SDS->SerializeData(), sizeof(SDS->TotalSize), 0);
}

int ServerConnection::setServerSocket(SOCKET newSocket)
{
	if (newSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return 1;
	}
	ServerSocket = newSocket;
	return 0;
}

int ServerConnection::setConnectionSocket()
{
	
	if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == INVALID_SOCKET)
	{
		socketCleanUp(ServerSocket);
		WSACleanup();
		return 1;
	}
	return 0;
}

void ServerConnection::changeTxBuffer(char* newTx)
{
	strcpy(TxBuffer, newTx);
}

void ServerConnection::closeServer() 
{
	socketCleanUp(ServerSocket);
	socketCleanUp(ConnectionSocket);
	WSACleanup();
}