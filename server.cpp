#include <windows.networking.sockets.h>
#include <iostream>
#include "Profile.h"
#include "serverConnection.h"
#include "header.h"
#include "vote.h"
#include "Password.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;
int main()
{
	ServerConnection server;
	WSAData wsaData;
	int bytesReceived;
	char* conversion;
	Packet CurrentPacket;
	Password* account;
	Vote* vote = (Vote*)calloc(1, sizeof(Vote));
	Profile* profile = (Profile*)calloc(1, sizeof(profile));
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
		CurrentPacket.DeserializeData(server.getRxBuffer());

		switch (CurrentPacket.getPacketType()) 
		{
		case(PacketTypes::LoginRequestPacket):
		{
			std::string data = CurrentPacket.getData();
			std::stringstream ss(data);
			std::string userID; 
			getline(ss, userID, ','); 

			if (!server.checkIDInFile("users.csv", std::stoi(userID))) 
			{ 
				std::cerr << "Can't Not Find This ID。" << std::endl;
				CurrentPacket.setPacketType(PacketTypes::NoAccessPacket);
				server.changeTxBuffer(CurrentPacket.SerializeData());
				server.sendMsg();
				break; 
			}

			account = new Password(CurrentPacket.getData());
			CurrentPacket.setData("");
			if (account->checkPassword(account->getUsername()))
			{
				CurrentPacket.setPacketType(PacketTypes::LoginSuccessPacket);
			}
			else
			{
				CurrentPacket.setPacketType(PacketTypes::NoAccessPacket);
			}
			server.changeTxBuffer(CurrentPacket.SerializeData());
			server.sendMsg();
			break;
		}

		case(PacketTypes::CreateProfilePacket): //profile packet
			profile = new Profile((CurrentPacket.getData())); //creates a profile from the packet
			break;

		case(PacketTypes::EditProfilePacket):
			if (account->checkPassword(profile->getUsername()))
			{
				profile->editProfile(CurrentPacket.getData());
			}
			else
			{
				CurrentPacket.setData("");
				CurrentPacket.setPacketType(PacketTypes::LoginRequestPacket);
				server.changeTxBuffer(CurrentPacket.SerializeData());
				server.sendMsg();
			}
			break;

		case(PacketTypes::VotePacket):
			profile = new Profile((CurrentPacket.getData()));
			vote = new Vote(*profile);
			break;

		case(PacketTypes::ProfileRequestPacket):
			profile = new Profile((CurrentPacket.getData()));
			memcpy(conversion, profile, sizeof(Profile));
			CurrentPacket.setData(conversion);
			server.changeTxBuffer(CurrentPacket.SerializeData());
			server.sendMsg();
			break;
		
	} while (bytesReceived > 0);

	server.closeServer();
	return 1;
}