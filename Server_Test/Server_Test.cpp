#include "pch.h"
#include "CppUnitTest.h"
//#include"../Testing/createProfile.h"
//#include"../Testing/editProfile.h"

//#include"../Testing/Logclass.h"
//#include"../Testing/LogOutServer.h"
//#include"../Testing/packet.h"
//#include"../Testing/Password.h"
//#include"../Testing/ReadDataServer.h"
//#include"../Testing/SendDataServer.h"
#include"../Testing/serverConnection.h"
//#include"../Testing/structDefinitions.h"
//#include"../Testing/vote.h"

#include"../Pre demo/ClientConnection.h"
//#include"../Pre demo/Logclass.h"
//#include"../Pre demo/packet.h"
//#include"../Pre demo/Password.h"
//#include"../Pre demo/ReadDataClient.h"
//#include"../Pre demo/SendDataClient.h"
//#include"../Pre demo/structDefinitions.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ServerTESTCase
{
	TEST_CLASS(UnitTests)
	{
	public:

		TEST_METHOD(Connection_Test_Pass)
		{
			

			ServerConnection server;
			WSAData wsaData;
			packetClass* TxPacket;

			WSAStartup(MAKEWORD(2, 2), &wsaData);
			server.setServerSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
			server.socketCreateBind();
			server.socketListenConnect();
			server.setConnectionSocket();
			
			ClientConnection client;

			// Connect to the server
			Assert::IsTrue((client.connectToServer("127.0.0.1", 27000) == 0));
		}

		TEST_METHOD(Connection_Test_Fail)
		{


			ServerConnection server;
			WSAData wsaData;
			packetClass* TxPacket;

			WSAStartup(MAKEWORD(2, 2), &wsaData);
			server.setServerSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
			server.socketCreateBind();
			server.socketListenConnect();
			server.setConnectionSocket();

			ClientConnection client;

			// Connect to the server
			Assert::IsFalse((client.connectToServer("127.0.0.1", 27000) == 0));
		}



	/*	TEST_METHOD(LoginRequestTest)
		{
			ClientConnection clientConnection;
			Assert::IsTrue(clientConnection.connectToServer("127.0.0.1", 27000) == 0, L"Cannot connect to server.");

			SendDataClient sendDataClient(clientConnection);
			packetClass loginPacket;
			std::string loginInfoString = "testUser,testPassword";
			loginPacket.loginInfo = Account(loginInfoString);
			loginPacket.Head.packetType = PacketTypes::LoginRequestPacket;
			sendDataClient.sendPacket(loginPacket);

			ReadDataClient readDataClient(clientConnection);
			packetClass responsePacket;
			readDataClient.receivePacket(responsePacket);
			Assert::AreEqual(static_cast<int>(PacketTypes::LoginSuccessPacket), static_cast<int>(responsePacket.Head.packetType), L"Login failed.");
		}*/
	};//

}