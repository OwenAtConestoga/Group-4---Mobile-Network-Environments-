#include <windows.networking.sockets.h>
#include <iostream>
#include "Profile.h"
#include "serverConnection.h"
#include "header.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;
int main()
{
	ServerConnection server;
	WSAData wsaData;
	int bytesReceived;
	Packet CurrentPacket;
	Profile* profile;
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
		
		switch (CurrentPacket.getPacketType()) {
		case(PacketTypes::CreateProfilePacket): //profile packet
			profile = new Profile(server.getRxBuffer()); //creates a profile from the packet
			break;
		case(PacketTypes::EditProfilePacket):
			profile->editProfile(server.getRxBuffer());
			break;
		case(PacketTypes::VotePacket):
			break;
		}
		
	} while (bytesReceived > 0);

	server.closeServer();
	return 1;
}