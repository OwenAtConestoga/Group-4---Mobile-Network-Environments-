#include "clientConnection.h"
#include "readDataClient.h"
#include "sendDataClient.h"
#include "LogClass.h"
#include "CreateProfile.h"
#include "EditProfile.h"
#include "Vote.h"
#include "Password.h"
#include "packet.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;


void logout(LogClass& logger){
    logger.PrintToFile("Login Out");
}

int main() {
    ClientConnection clientConnection;
    CreateProfile createProfile;
    EditProfile editProfile;
    Vote vote;
    ReadDataClient readDataClient(clientConnection);
    SendDataClient sendDataClient(clientConnection);
    LogClass logger("log.csv");
    int totalSize = 0;

    // Connect to the server
    if (clientConnection.connectToServer("127.0.0.1", 27000) != 0) {
        cout << "Failed to connect to the server." << endl;
        return 1;
    }

    // Login
    packetClass loginPacket;
    loginPacket.Head.packetType = PacketTypes::LoginRequestPacket;
    cout << "Enter username: ";
    string username;
    cin >> username;
    cout << "Enter password: ";
    string password;
    cin >> password;
    loginPacket.loginInfo = Account(username + "," + password);
    sendDataClient.sendPacket(loginPacket);
    readDataClient.receivePacket(loginPacket);

    if (loginPacket.Head.packetType == PacketTypes::LoginSuccessPacket) {
        cout << "Login successful." << endl;
        logger.PrintToFile("Login Successful: " + loginPacket.loginInfo.username + "," + loginPacket.loginInfo.password);
        int choice;
        int running = 1;
        while (running) {
            cout << "1. Create Profile" << endl;
            cout << "2. Edit Profile" << endl;
            cout << "3. Vote" << endl;
            cout << "4. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                createProfile.createProfile(username, sendDataClient, readDataClient, logger);
                break;
            case 2:
                editProfile.editProfile(username, sendDataClient, readDataClient, logger);
                break;
            case 3:
                vote.vote(username, sendDataClient, readDataClient, logger);
                break;
            case 4:
                logout(logger);
                cout << "Logout" << endl;
                running = 0;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }

        }
    }
    else {
        cout << "Login failed." << endl;
        logger.PrintToFile("Login Failed: " + loginPacket.loginInfo.username + "," + loginPacket.loginInfo.password);
        return 1;
    }

    return 0;
}