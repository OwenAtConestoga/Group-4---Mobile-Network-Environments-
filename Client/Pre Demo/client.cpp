#include "clientConnection.h"
#include "readDataClient.h"
#include "sendDataClient.h"
#include "LogClass.h"
#include "Password.h"
#include "packet.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    ClientConnection clientConnection;
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
    loginPacket.loginInfo.username = username;
    loginPacket.loginInfo.password = password;
    sendDataClient.sendPacket(loginPacket);
    
    cout << loginPacket.loginInfo.username << endl;
    cout << loginPacket.loginInfo.password << endl;
    readDataClient.receivePacket(loginPacket);
    cout << loginPacket.loginInfo.username << endl;
    cout << loginPacket.loginInfo.password << endl;

    if (loginPacket.Head.packetType == PacketTypes::LoginSuccessPacket) {
        cout << "Login successful." << endl;
        logger.PrintToFile("Login Successful: " + loginPacket.loginInfo.username + "," + loginPacket.loginInfo.password);
    }
    else {
        cout << "Login failed." << endl;
        logger.PrintToFile("Login Failed: " + loginPacket.loginInfo.username + "," + loginPacket.loginInfo.password);
        return 1;
    }

    // Create profile
    packetClass createProfilePacket;

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
    createProfilePacket.profile.firstName = firstName;
    createProfilePacket.profile.lastName = lastName;
    createProfilePacket.profile.bio = bio;
    createProfilePacket.profile.userClass = userClass;
    createProfilePacket.Head.packetType = PacketTypes::CreateProfilePacket;
    sendDataClient.sendPacket(createProfilePacket);
    //readDataClient.receivePacket(createProfilePacket);
    sendDataClient.sendPacket(createProfilePacket);
    readDataClient.receivePacket(createProfilePacket);

    if (createProfilePacket.Head.packetType == PacketTypes::LoginSuccessPacket) {
        cout << "Profile created successfully." << endl;
        ostringstream profileStream;
        profileStream << createProfilePacket.profile.userName << ","
            << createProfilePacket.profile.firstName << ","
            << createProfilePacket.profile.lastName << ","
            << createProfilePacket.profile.bio << ","
            << createProfilePacket.profile.userClass << ","
            << createProfilePacket.profile.id << ","
            << createProfilePacket.profile.voteCount;
        logger.PrintToFile("Profile Created: " + profileStream.str());
    }
    else {
        cout << "Profile creation failed." << endl;
        ostringstream profileStream;
        profileStream << createProfilePacket.profile.userName << ","
            << createProfilePacket.profile.firstName << ","
            << createProfilePacket.profile.lastName << ","
            << createProfilePacket.profile.bio << ","
            << createProfilePacket.profile.userClass << ","
            << createProfilePacket.profile.id << ","
            << createProfilePacket.profile.voteCount;
        logger.PrintToFile("Profile Created: " + profileStream.str());
    }

    // Edit profile
    packetClass editProfilePacket;
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
    Profile newProfile(firstName + "," + lastName + "," + bio + "," + userClass + "," + to_string(profileID) + ",0");
    editProfilePacket.profile = newProfile;
    sendDataClient.sendPacket(editProfilePacket);
    readDataClient.receivePacket(editProfilePacket);

    if (editProfilePacket.Head.packetType == PacketTypes::LoginSuccessPacket) {
        cout << "Profile edited successfully." << endl;
        ostringstream profileStream;
        profileStream << createProfilePacket.profile.userName << ","
            << createProfilePacket.profile.firstName << ","
            << createProfilePacket.profile.lastName << ","
            << createProfilePacket.profile.bio << ","
            << createProfilePacket.profile.userClass << ","
            << createProfilePacket.profile.id << ","
            << createProfilePacket.profile.voteCount;
        logger.PrintToFile("Profile Created: " + profileStream.str());
    }
    else {
        cout << "Profile edit failed." << endl;
        ostringstream profileStream;
        profileStream << createProfilePacket.profile.userName << ","
            << createProfilePacket.profile.firstName << ","
            << createProfilePacket.profile.lastName << ","
            << createProfilePacket.profile.bio << ","
            << createProfilePacket.profile.userClass << ","
            << createProfilePacket.profile.id << ","
            << createProfilePacket.profile.voteCount;
        logger.PrintToFile("Profile Edited: " + profileStream.str());
    }

    // Vote
    packetClass votePacket;
    votePacket.Head.packetType = PacketTypes::VotePacket;
    cout << "Enter profile ID to vote: ";
    cin >> profileID;
    votePacket.profile = Profile(to_string(profileID) + ",1");
    sendDataClient.sendPacket(votePacket);
    readDataClient.receivePacket(votePacket);

    if (votePacket.Head.packetType == PacketTypes::LoginSuccessPacket) {
        cout << "Vote recorded successfully." << endl;
        ostringstream profileStream;
        profileStream << createProfilePacket.profile.userName << ","
            << createProfilePacket.profile.firstName << ","
            << createProfilePacket.profile.lastName << ","
            << createProfilePacket.profile.bio << ","
            << createProfilePacket.profile.userClass << ","
            << createProfilePacket.profile.id << ","
            << createProfilePacket.profile.voteCount;
        logger.PrintToFile("Profile Created: " + profileStream.str());
    }
    else {
        cout << "Vote failed." << endl;
        ostringstream profileStream;
        profileStream << createProfilePacket.profile.userName << ","
            << createProfilePacket.profile.firstName << ","
            << createProfilePacket.profile.lastName << ","
            << createProfilePacket.profile.bio << ","
            << createProfilePacket.profile.userClass << ","
            << createProfilePacket.profile.id << ","
            << createProfilePacket.profile.voteCount;
        logger.PrintToFile("Vote Created: " + profileStream.str());
    }
    Sleep(10000);
    return 0;
}