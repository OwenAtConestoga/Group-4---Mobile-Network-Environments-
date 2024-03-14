#include <windows.networking.sockets.h>
#include <iostream>
#include "Profile.h"
#include "serverConnection.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;
int main()
{
	ServerConnection server;
	WSAData wsaData;
	int bytesReceived;
	int packetType;
	// Sets up the server
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { return 0; }
	if (server.setServerSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != 0) { return 0; }
	if (server.socketCreateBind()) { return 0; }
	if (server.socketListenConnect()) { return 0; }
	if (server.setConnectionSocket() != 0){	return 0; }

	// Accepts and recieves messages
	do 
	{
		bytesReceived = server.recvMsg();
		server.changeRxBuffer(server.getRxBuffer() + '\0');

		switch (packetType) {
		case(0): //profile packet
			Profile profile(server.getRxBuffer()); //creates a profile from the packet
		}
		
	} while (bytesReceived > 0);

	server.closeServer();
	return 1;
}