
#include "Vote.h"

void Vote::vote(string username, SendDataClient& sendDataClient, ReadDataClient& readDataClient, LogClass& logger) {
    int profileID;
    packetClass createProfilePacket;
    packetClass votePacket;
    votePacket.Head.packetType = PacketTypes::VotePacket;
    cout << "Enter profile ID to vote: ";
    cin >> profileID;
    votePacket.profile = Profile(username + ", , , , ," + to_string(profileID) + ", ");
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