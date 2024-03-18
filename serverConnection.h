#pragma once
#include <windows.networking.sockets.h>
#include <iostream>
#include "Profile.h"
#include "header.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class ServerConnection {
	Header head;
	int CRC;
	char* TxBuffer;
	char* RxBuffer;
	struct Packet;
	SOCKET ServerSocket;
	SOCKET ConnectionSocket;

public:
	int socketCreateBind();
	void socketCleanUp(SOCKET);
	int socketListenConnect();
	int recvMsg();
	void sendMsg();
	void changeTxBuffer(char*);
	void changeRxBuffer(char*);
	int setServerSocket(SOCKET);
	int setConnectionSocket();
	char* getRxBuffer();
	void closeServer();
	bool checkIDInFIle(const std::string& filename, int searchID);
};