#include "clientConnection.h"
#include "readDataClient.h"
#include "sendDataClient.h"
//#include "LogClass.h"
//#include "Password.h"
//#include "createProfile.h"
//#include "editProfile.h"
//#include "Vote.h"
#include "structDefinitions.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    int totalSize = 0;
    ClientConnection clientConnection;
    ReadDataClient readDataClient(clientConnection);
    SendDataClient sendDataClient(clientConnection);
    //LogClass logger("log.csv", totalSize);
    //Password password("usr.csv");

    // Connect to the server
    if (clientConnection.connectToServer("127.0.0.1", 27000) != 0) {
        cout << "Failed to connect to the server." << endl;
        return 1;
    }

    // Login
    Packet loginPacket;
    loginPacket.Head.packetType = PacketTypes::LoginRequestPacket;
    cout << "Enter username: ";
    string username;
    cin >> username;
    cout << "Enter password: ";
    string password;
    cin >> password;
    loginPacket.dataField = username + ":" + password;
    sendDataClient.sendPacket(loginPacket);
    readDataClient.receivePacket(loginPacket);

    if (loginPacket.Head.packetType == PacketTypes::LoginSuccessPacket) {
        cout << "Login successful." << endl;
        //logger.PrintToFile("Login Successful: " + loginPacket.dataField);
    }
    else {
        cout << "Login failed." << endl;
        //logger.PrintToFile("Login Failed: " + loginPacket.dataField);
        return 1;
    }

    // Create profile
    Packet createProfilePacket;
    createProfilePacket.Head.packetType = PacketTypes::CreateProfilePacket;
    cout << "Enter profile information:" << endl;
    cout << "First name: ";
    string firstName;
    cin >> firstName;
    cout << "Last name: ";
    string lastName;
    cin >> lastName;
    cout << "Bio: ";
    string bio;
    cin >> bio;
    cout << "User class: ";
    string userClass;
    cin >> userClass;
    createProfilePacket.dataField = firstName + "," + lastName + "," + bio + "," + userClass;
    sendDataClient.sendPacket(createProfilePacket);
    readDataClient.receivePacket(createProfilePacket);

    if (createProfilePacket.Head.packetType == PacketTypes::LoginSuccessPacket) {
        cout << "Profile created successfully." << endl;
        //logger.PrintToFile("Profile Created: " + createProfilePacket.dataField);
    }
    else {
        cout << "Profile creation failed." << endl;
        //logger.PrintToFile("Profile Creation Failed: " + createProfilePacket.dataField);
    }

    // Edit profile
    Packet editProfilePacket;
    editProfilePacket.Head.packetType = PacketTypes::EditProfilePacket;
    cout << "Enter profile ID to edit: ";
    int profileID;
    cin >> profileID;
    cout << "Enter new profile information:" << endl;
    cout << "First name: ";
    cin >> firstName;
    cout << "Last name: ";
    cin >> lastName;
    cout << "Bio: ";
    cin >> bio;
    cout << "User class: ";
    cin >> userClass;
    editProfilePacket.dataField = to_string(profileID) + ":" + firstName + "," + lastName + "," + bio + "," + userClass;
    sendDataClient.sendPacket(editProfilePacket);
    readDataClient.receivePacket(editProfilePacket);

    if (editProfilePacket.Head.packetType == PacketTypes::LoginSuccessPacket) {
        cout << "Profile edited successfully." << endl;
        //logger.PrintToFile("Profile Edited: " + editProfilePacket.dataField);
    }
    else {
        cout << "Profile edit failed." << endl;
        //logger.PrintToFile("Profile Edit Failed: " + editProfilePacket.dataField);
    }

    // Vote
    Packet votePacket;
    votePacket.Head.packetType = PacketTypes::VotePacket;
    cout << "Enter profile ID to vote: ";
    cin >> profileID;
    votePacket.dataField = to_string(profileID);
    sendDataClient.sendPacket(votePacket);
    readDataClient.receivePacket(votePacket);

    if (votePacket.Head.packetType == PacketTypes::LoginSuccessPacket) {
        cout << "Vote recorded successfully." << endl;
        //logger.PrintToFile("Vote Recorded: " + votePacket.dataField);
    }
    else {
        cout << "Vote failed." << endl;
        //logger.PrintToFile("Vote Failed: " + votePacket.dataField);
    }

    return 0;
}

