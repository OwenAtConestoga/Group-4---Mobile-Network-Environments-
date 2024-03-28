#include "serverConnection.h"
#include <sstream>
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

bool ServerConnection::checkIDInFile(const std::string& filename, int searchID) {
	std::ifstream file(filename);
	std::string line;
	if (!file.is_open()) 
	{
		std::cerr << "Can't Open This File" << std::endl;
		return false;
	}

	while (getline(file, line)) 
	{
		std::stringstream ss(line);
		std::string item;
		getline(ss, item, ',');

		try {
			int fileID = std::stoi(item);	//Change String to Integer 

			if (fileID == searchID) 
			{
				return true; // Find ID
			}
		}
		catch (const std::invalid_argument& ia) 
		{
			std::cerr << "Wrong ID: " << item << std::endl;
		}
	}

	return false; // Cant't find ID
}