#pragma once
#include <windows.networking.sockets.h>
#include <iostream>
#include "structDefinitions.h"
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


public:
	int socketCreateBind();
	void socketCleanUp(SOCKET);
	int socketListenConnect();
	int recvMsg();
	void sendMsg();
	int setServerSocket(SOCKET);
	int setConnectionSocket();
	char* getRxBuffer();
	void closeServer();
	bool checkIDInile(const std::string& filename, int searchID);
};