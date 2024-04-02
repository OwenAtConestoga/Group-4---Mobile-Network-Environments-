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
int main() {
    ServerConnection server;
    WSAData wsaData;
    int bytesReceived;
    int totalSize = 0;      // Used for logging
    LogClass logger("log.csv", totalSize);

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
            Packet receivedPacket;

            switch (receivedPacket.Head.packetType)
            {
            case PacketTypes::LoginRequestPacket:
            {
                // Uses Password class to validate login credentials
                char* data = const_cast<char*>(receivedPacket.dataField.c_str());
                Password account(data);         // Constructs Password object
                if (account.checkPassword())
                {
                    receivedPacket.Head.packetType = PacketTypes::LoginSuccessPacket;
                    receivedPacket.dataField = "Login successful";
                }
                else
                {
                    receivedPacket.Head.packetType = PacketTypes::NoAccessPacket;
                    receivedPacket.dataField = "Login failed";
                }
                logger.PrintToFile("Login Attempt: " + receivedPacket.dataField);       // Logs

                break;
            }

            case PacketTypes::CreateProfilePacket:
            {
                // Uses createProfile class to creat new profile 
                char* data = const_cast<char*>(receivedPacket.dataField.c_str());
                createProfile profile(data, totalSize);         // Constructs createProfile object and parses profile data
                profile.saveInfoToFile("profiles.csv");         // Saves into file
                receivedPacket.Head.packetType = PacketTypes::LoginSuccessPacket;
                receivedPacket.dataField = "Profile created successfully";
                logger.PrintToFile("Profile Created: " + receivedPacket.dataField); // Logs

                break;
            }
            case PacketTypes::EditProfilePacket:
            {
                // Uses editProfile class to edit profile 
                size_t delimiterPos = receivedPacket.dataField.find(":");
                int profileID = stoi(receivedPacket.dataField.substr(0, delimiterPos));
                string newProfileData = receivedPacket.dataField.substr(delimiterPos + 1);

                editProfile editor(profileID, totalSize, "_profile.csv");       // Constructs editProfile object for the specified profile Or you can change to profile.csv. change the path if need

                char* newData = const_cast<char*>(newProfileData.c_str());
                editor.updateProfile(strtok(newData, ","), strtok(NULL, ","), strtok(NULL, ","), strtok(NULL, ","), strtok(NULL, ",")); // Updates profile data

                editor.updateFile(); // Writes changes back to the file
                receivedPacket.Head.packetType = PacketTypes::LoginSuccessPacket;
                receivedPacket.dataField = "Profile edited successfully";
                logger.PrintToFile("Profile Edited: " + receivedPacket.dataField);      // Logs

                break;
            }
            case(PacketTypes::VotePacket):
            {
                // Uses Vote class increment vote count for a profile
                int profileID = stoi(receivedPacket.dataField);         // Extracts profile ID from dataField
                Vote vote;
                vote.addVote(profileID);
                receivedPacket.Head.packetType = PacketTypes::LoginSuccessPacket;
                receivedPacket.dataField = "Vote recorded successfully";
                logger.PrintToFile("Vote Recorded: " + receivedPacket.dataField);       // Logs

                break;
            }
            case(PacketTypes::ProfileRequestPacket):
            {
                // Uses Vote class to fetch a profile's data
                int profileID = stoi(receivedPacket.dataField);         // Extracts profile ID for the request
                Vote vote;
                string profileData = vote.GetDataFromID("profiles.csv", profileID);         // Fetches the profile data, change path if neeed
                if (!profileData.empty())
                {
                    receivedPacket.Head.packetType = PacketTypes::ProfileRequestPacket;
                    receivedPacket.dataField = profileData;         // Sets the fetched data as the dataField of the Packet
                }
                else
                {
                    receivedPacket.Head.packetType = PacketTypes::NoAccessPacket;
                    receivedPacket.dataField = "Profile not found";
                }

                logger.PrintToFile("Profile Requested: ID " + to_string(profileID));        // Logs

                break;
            }

            }

            // Serialize and send the Packet back to the client
            SendDataServer sendData(totalSize, (char*)&receivedPacket);         // Prepares the response Packet
            server.changeTxBuffer(sendData.SerializeData());        // Serializes and sets the response data
            server.sendMsg();       // Sends the response back to the client
        }
    } while (bytesReceived > 0);

    server.closeServer();       // Cleans up and closes the server socket
    return 1;
}