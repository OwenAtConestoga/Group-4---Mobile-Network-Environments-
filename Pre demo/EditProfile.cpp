#include "EditProfile.h"


void EditProfile::editProfile(string username, SendDataClient& sendDataClient, ReadDataClient& readDataClient, LogClass& logger) {
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