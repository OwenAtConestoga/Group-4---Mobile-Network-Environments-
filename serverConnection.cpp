#include "serverConnection.h"

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
		return 0;
	}
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
		return 0;
	}
}

int ServerConnection::recvMsg()
{
	return recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
}

void ServerConnection::sendMsg()
{
	send(ConnectionSocket, TxBuffer, sizeof(TxBuffer), 0);
}

void ServerConnection::changeTxBuffer(char* input)
{
	TxBuffer = input;
}

void ServerConnection::changeRxBuffer(char* output)
{
	RxBuffer = output;
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

char* ServerConnection::getRxBuffer()
{
	return RxBuffer;
}

void ServerConnection::closeServer() 
{
	socketCleanUp(ServerSocket);
	socketCleanUp(ConnectionSocket);
	WSACleanup();
}