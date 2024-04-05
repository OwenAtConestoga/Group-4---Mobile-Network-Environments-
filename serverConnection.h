#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
	Packet pkt;
	SOCKET ServerSocket;
	SOCKET ConnectionSocket;

public:
	SendDataServer* SDS;
	ReadDataServer* RDS;
	ServerConnection();
	int socketCreateBind();
	void socketCleanUp(SOCKET);
	int socketListenConnect();
	int recvMsg();
	void sendMsg(packetClass);
	int setServerSocket(SOCKET);
	int setConnectionSocket();
	void changeTxBuffer(char* newTx);
	void closeServer();
};