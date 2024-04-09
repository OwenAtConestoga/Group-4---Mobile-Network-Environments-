#include "pch.h"
#include "CppUnitTest.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "../Pre demo/ClientConnection.h"
#include "../Pre demo/ReadDataClient.h"
#include "../Pre demo/SendDataClient.h"
#include "../Pre demo/SendDataClient.cpp"
#include "../Pre demo/ReadDataClient.cpp"
#include "../Pre demo/ClientConnection.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ServerTESTCase
{
    TEST_CLASS(ServerConnectionTests)
    {
    public:
        TEST_METHOD(SessionConnectionTest)
        {
            bool pass = true;
            ClientConnection clientConnection;
            if (clientConnection.connectToServer("127.0.0.1", 27000) != 0) {
                cout << "Failed to connect to the server." << endl;
                pass = false;
            }
            Assert::IsTrue(pass);
        }

        TEST_METHOD(LoginRequestTest)
        {
            ClientConnection clientConnection;
            if (clientConnection.connectToServer("127.0.0.1", 27000) != 0) {
                cout << "Failed to connect to the server." << endl;
                Assert::Fail();
            }
            SendDataClient sendDataClient(clientConnection);
            packetClass loginPacket;
            loginPacket.loginInfo.username = "testUser";
            loginPacket.loginInfo.password = "testPassword";
            loginPacket.Head.packetType = PacketTypes::LoginRequestPacket;
            sendDataClient.sendPacket(loginPacket);

            ReadDataClient readDataClient(clientConnection);
            packetClass responsePacket;
            readDataClient.receivePacket(responsePacket);
            Assert::AreEqual(static_cast<int>(PacketTypes::LoginSuccessPacket), static_cast<int>(responsePacket.Head.packetType));
        }
    };

}