#pragma once
#include <windows.networking.sockets.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ReadDataServer.h"
#include "SendDataServer.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class ServerConnection {
	Header head;
	int CRC;
	char* TxBuffer;
	char* RxBuffer;
	Packet pkt;
	SOCKET ServerSocket;
	SOCKET ConnectionSocket;
	ReadDataServer RDS;
	SendDataServer SDS;
	
	

public:
	ServerConnection();
	int socketCreateBind();
	void socketCleanUp(SOCKET);
	int socketListenConnect();
	int recvMsg();
	void sendMsg();
	int setServerSocket(SOCKET);
	int setConnectionSocket();
	void closeServer();
	bool checkIDInFIle(const std::string& filename, int searchID);
};