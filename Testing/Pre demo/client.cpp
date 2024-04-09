#include "clientConnection.h"
#include "readDataClient.h"
#include "sendDataClient.h"
#include "LogClass.h"
#include "Password.h"
#include "packet.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

void createProfile(string username, SendDataClient& sendDataClient, ReadDataClient& readDataClient, LogClass& logger) {
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

    //create random id
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 10000);
    int id = dis(gen);

    createProfilePacket.profile = Profile(username + "," + firstName + "," + lastName + "," + bio + "," + userClass + "," + to_string(id) + ",0");
    sendDataClient.sendPacket(createProfilePacket);
    readDataClient.receivePacket(createProfilePacket);

    if (createProfilePacket.Head.packetType == PacketTypes::ProfileRequestPacket) {
        cout << "Profile created successfully." << endl;
        cout << "Your Profile id is " << id << endl;
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
}

void editProfile(string username, SendDataClient& sendDataClient, ReadDataClient& readDataClient, LogClass& logger) {
    packetClass createProfilePacket;
    packetClass profileRequestPacket;
    profileRequestPacket.Head.packetType = PacketTypes::ProfileRequestPacket;
    cout << "Enter profile ID to edit: ";
    int profileID;
    cin >> profileID;
    Profile askProfile(username + ", , , ," + to_string(profileID) + ",0");
    profileRequestPacket.profile = askProfile;
    sendDataClient.sendPacket(profileRequestPacket);
    readDataClient.receivePacket(profileRequestPacket);

    if (profileRequestPacket.Head.packetType == PacketTypes::ProfileRequestPacket) {
        // Edit profile
        packetClass editProfilePacket;
        editProfilePacket.Head.packetType = PacketTypes::EditProfilePacket;
        cout << "Enter new profile information:" << endl;
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
        Profile newProfile(username + "," + firstName + "," + lastName + "," + bio + "," + userClass + "," + to_string(profileID) + ",0");
        editProfilePacket.profile = newProfile;
        sendDataClient.sendPacket(editProfilePacket);
        readDataClient.receivePacket(editProfilePacket);
        cout << "Profile edited successfully." << endl;
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
    else {
        cout << "Profile not existed." << endl;
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
}

void vote(string username, SendDataClient& sendDataClient, ReadDataClient& readDataClient, LogClass& logger) {
    int profileID;
    packetClass createProfilePacket;
    packetClass votePacket;
    votePacket.Head.packetType = PacketTypes::VotePacket;
    cout << "Enter profile ID to vote: ";
    cin >> profileID;
    votePacket.profile = Profile(username+ ", , , , ," + to_string(profileID) + ", ");
    sendDataClient.sendPacket(votePacket);
    readDataClient.receivePacket(votePacket);

    if (votePacket.Head.packetType == PacketTypes::VotePacket) {
        cout << "Vote recorded successfully." << endl;
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
}


void logout(LogClass& logger){
    logger.PrintToFile("Login Out");
}

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
                createProfile(username, sendDataClient, readDataClient, logger);
                break;
            case 2:
                editProfile(username, sendDataClient, readDataClient, logger);
                break;
            case 3:
                vote(username, sendDataClient, readDataClient, logger);
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