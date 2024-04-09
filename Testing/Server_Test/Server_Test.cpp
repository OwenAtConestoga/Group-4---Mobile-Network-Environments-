#include "pch.h"
#include "CppUnitTest.h"
#include"../Server_Test/createProfile.h"
#include"../Server_Test/editProfile.h"
#include"../Server_Test/Logclass.h"
#include"../Server_Test/LogOutServer.h"
#include"../Server_Test/packet.h"
#include"../Server_Test/Password.h"
#include"../Server_Test/ReadDataServer.h"
#include"../Server_Test/SendDataServer.h"
#include"../Server_Test/serverConnection.h"
#include"../Server_Test/structDefinitions.h"
#include"../Server_Test/vote.h"

#include"../Client_Test/ClientConnection.h"
#include"../Client_Test/Logclass.h"
#include"../Client_Test/packet.h"
#include"../Client_Test/Password.h"
#include"../Client_Test/ReadDataClient.h"
#include"../Client_Test/SendDataClient.h"
#include"../Client_Test/structDefinitions.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ServerTESTCase
{
    TEST_CLASS(ServerConnectionTests)
    {
    public:

        TEST_METHOD(LoginRequestTest)
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
        }
    };

}