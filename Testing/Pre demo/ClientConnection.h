#pragma once
#include <winsock2.h>

class ClientConnection {
private:
    WSADATA wsaData;
    SOCKET serverSocket;
    SOCKADDR_IN serverAddr;

public:
    ClientConnection();
    ~ClientConnection();
    int connectToServer(const char* serverIP, int serverPort);
    int sendData(char* data, int dataSize);
    int receiveData(char* buffer, int bufferSize);
};