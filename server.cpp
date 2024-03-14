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

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { return 0; }
	if (server.setServerSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != 0) { return 0; }
	if (server.socketCreateBind()) { return 0; }
	if (server.socketListenConnect()) { return 0; }
	if (server.setConnectionSocket() != 0){	return 0; }

	do 
	{
		bytesReceived = server.recvMsg();
		server.changeRxBuffer(server.getRxBuffer() + '\0');
		// Deserialize the received data into a Profile object and save/update
		Profile profile = Profile::deserialize(string(server.getRxBuffer()));
		profile.saveToFile("profiles.txt"); // Save to prifile.txt, if need we can change the path
	} while (bytesReceived > 0);

	server.closeServer();
	return 1;
}