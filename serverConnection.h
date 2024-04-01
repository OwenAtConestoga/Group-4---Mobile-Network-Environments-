#pragma once
#include <windows.networking.sockets.h>
#include <iostream>
#include "structDefinitions.h"
#include "ReadDataServer.h"
#include "SendDataServer.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class ServerConnection {
	int CRC;
	char* TxBuffer;
	char* RxBuffer;
	SendDataServer* SDS;
	ReadDataServer* RDS;
	Packet pkt;
	SOCKET ServerSocket;
	SOCKET ConnectionSocket;

public:
	ServerConnection();
	int socketCreateBind();
	void socketCleanUp(SOCKET);
	int socketListenConnect();
	int recvMsg();
	void sendMsg();
	int setServerSocket(SOCKET);
	int setConnectionSocket();
	void changeTxBuffer(char* newTx);
	void closeServer();
};