#define _CRT_SECURE_NO_WARNINGS
#include <windows.networking.sockets.h>
#include <iostream>
#include <sstream>
#include "LogClass.h"
#include "serverConnection.h"
#include "Password.h"
#include "createProfile.h"
#include "editProfile.h"
#include "Vote.h"
#include "structDefinitions.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;
int main() 
{
    ServerConnection server;
    WSAData wsaData;
    packetClass* TxPacket;
    int bytesReceived;
    int totalSize = 0;      // Used for logging

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { return 0; }
    if (server.setServerSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != 0) { return 0; }
    if (server.socketCreateBind()) { return 0; }
    if (server.socketListenConnect()) { return 0; }
    if (server.setConnectionSocket() != 0) { return 0; }

    do
    {
        bytesReceived = server.recvMsg();

        if (bytesReceived > 0)
        {
            TxPacket = new packetClass();
            if (!server.RDS->LOS.isLoggedIn() && server.RDS->pktClass.Head.packetType != PacketTypes::LoginRequestPacket)
            {
                TxPacket->Head.packetType = PacketTypes::NoAccessPacket;
                server.sendMsg(*TxPacket);
            }
            else {
                switch (server.RDS->pktClass.Head.packetType)
                {
                case PacketTypes::LoginRequestPacket:
                {
                    if (server.RDS->login(server.RDS->pktClass.loginInfo))
                    {
                        TxPacket->Head.packetType = PacketTypes::LoginSuccessPacket;
                        server.RDS->logFile("--Login Request--\n", server.RDS->serverFeedBack(ResponseCodes::ACCEPTED));
                    }
                    else
                    {
                        TxPacket->Head.packetType = PacketTypes::NoAccessPacket;
                        server.RDS->logFile("--Login Request--\n", server.RDS->serverFeedBack(ResponseCodes::UNAUTHORIZED));
                    }

                    server.sendMsg(*TxPacket);
                    break;
                }

                case PacketTypes::CreateProfilePacket:
                {
                    // Uses createProfile class to create new profile 
                    createProfile profile((char*)static_cast<string>(server.RDS->pktClass.profile).c_str());
                    profile.saveInfoToFile("profiles.csv");
                    server.RDS->logFile("--Profile Created--\n", server.RDS->serverFeedBack(ResponseCodes::OK));
                    TxPacket->Head.packetType = PacketTypes::ProfileRequestPacket;
                    server.sendMsg(*TxPacket);
                    break;
                }
                case PacketTypes::EditProfilePacket:
                {
                    editProfile editor(server.RDS->pktClass.profile.id, "profiles.csv");
                    editor.updateProfile(server.RDS->pktClass.profile);
                    editor.updateFile(); // Writes changes back to the file
                    TxPacket->Head.packetType = PacketTypes::LoginSuccessPacket;
                    server.RDS->logFile("--Profile Edited--\n", server.RDS->serverFeedBack(ResponseCodes::OK));
                    TxPacket->Head.packetType = PacketTypes::EditProfilePacket;
                    server.sendMsg(*TxPacket);
                    break;
                }
                case(PacketTypes::VotePacket):
                {
                    Vote vote;
                    vote.addVote(server.RDS->pktClass.profile.id);
                    server.RDS->logFile("--Vote Recorded--\n", server.RDS->serverFeedBack(ResponseCodes::OK));
                    TxPacket->Head.packetType = PacketTypes::VotePacket;
                    server.sendMsg(*TxPacket);
                    break;
                }
                case(PacketTypes::ProfileRequestPacket):
                {

                    Vote vote;
                    string profileData = vote.GetDataFromID(server.RDS->pktClass.profile.id, "profiles.csv");         // Fetches the profile data, change path if need
                    if (!profileData.empty())
                    {
                        TxPacket->Head.packetType = PacketTypes::ProfileRequestPacket;
                        server.RDS->logFile("--Requested Data--\n", server.RDS->serverFeedBack(ResponseCodes::OK));
                    }
                    else
                    {
                        TxPacket->Head.packetType = PacketTypes::NoAccessPacket;
                        server.RDS->logFile("--Requested Data--\n", server.RDS->serverFeedBack(ResponseCodes::NOCONTENT));
                    }
                    istringstream dataStream(profileData);
                    getline(dataStream, TxPacket->profile.userName, ',');
                    getline(dataStream, TxPacket->profile.firstName, ',');
                    getline(dataStream, TxPacket->profile.lastName, ',');
                    getline(dataStream, TxPacket->profile.bio, ',');
                    getline(dataStream, TxPacket->profile.userClass, ',');
                    string idStr, voteCountStr;
                    getline(dataStream, idStr, ',');
                    TxPacket->profile.id = stoi(idStr);
                    getline(dataStream, voteCountStr, ',');
                    TxPacket->profile.voteCount = stoi(voteCountStr);
                    break;
                }
                case(PacketTypes::LogoutPacket):
                {
                    server.RDS->LogOut();
                    server.RDS->logFile("--Logout Request--\n", server.RDS->serverFeedBack(ResponseCodes::OK));
                    TxPacket->Head.packetType = PacketTypes::LogoutPacket;
                    server.sendMsg(*TxPacket);
                }
                case(PacketTypes::ProfileStreamPacket):
                {
                    int profileCount = 1;
                    std::ifstream file("profiles.csv");
                    std::string line;

                    if (!file.is_open()) {
                        std::cerr << "Unable to open file: " << "profiles.csv" << std::endl;
                        break;
                    }

                    while (std::getline(file, line)) {
                        if (line.empty()) {
                            break;
                        }
                        TxPacket->profile = *new Profile(line);
                        server.RDS->logFile("--Requested Profile Stream: Profile #" + to_string(profileCount++) + "--\n", server.RDS->serverFeedBack(ResponseCodes::OK));
                        TxPacket->Head.packetType = PacketTypes::ProfileStreamPacket;
                        server.sendMsg(*TxPacket);
                    }
                    TxPacket->profile = *new Profile();
                    TxPacket->Head.packetType = PacketTypes::EndOfProfileStreamPacket;
                    server.RDS->logFile("--End of Profile Transmission--\n", server.RDS->serverFeedBack(ResponseCodes::OK));
                    server.sendMsg(*TxPacket);
                    break;
                }
                }
            }
        }
    } while (true);

    server.closeServer();       // Cleans up and closes the server socket
    return 1;
}