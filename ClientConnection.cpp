#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "clientConnection.h"
#include <windows.networking.sockets.h>
//#include <arpa/inet.h> // For inet_addr
//#include <sys/socket.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

ClientConnection::ClientConnection() {
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

ClientConnection::~ClientConnection() {
    closesocket(serverSocket);
    WSACleanup();
}

int ClientConnection::connectToServer(const char* serverIP, int serverPort) {
    //sockaddr_in SvrAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    /*if (InetPton(AF_INET, serverIP, &serverAddr.sin_addr.s_addr) != 1) {
        return -1;
    }*/
    serverAddr.sin_port = htons(serverPort);

    if (connect(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        return -1;
    }

    return 0;
}

int ClientConnection::sendData(char* data, int dataSize) {
    return send(serverSocket, data, dataSize, 0);
}

int ClientConnection::receiveData(char* buffer, int bufferSize) {
    return recv(serverSocket, buffer, bufferSize, 0);
}
