#pragma once
#include <iostream>
#include <sstream>

using namespace std;
enum class PacketTypes {
    CreateProfilePacket,
    EditProfilePacket,
    VotePacket,
    ProfileRequestPacket,
    LoginRequestPacket,
    NoAccessPacket,
    LoginSuccessPacket,
    InvalidPacket
};

struct Header
{
    PacketTypes packetType;
    int Length;
    int NumOfBytes;
};

struct Profile
{
    std::string userName;
    std::string firstName;
    std::string lastName;
    std::string bio;
    std::string userClass;
    int id;
    int voteCount;

    //Initialize all member variables
    Profile() : userName(""), firstName(""), lastName(""), bio(""), userClass(""), id(0), voteCount(0) {}

    operator string() const {
        std::ostringstream oss;
        oss << userName << ',' << firstName << ',' << lastName << ',' << bio << ',' << userClass << ',' << id << ',' << voteCount;
        return oss.str();
    }
};

struct Packet
{
    Header Head;
    string dataField;
    Profile profile; // Added the Profile structure into the Packet
    unsigned int CRC;
    const unsigned int CONSTCRC = 0xFF00FF00;
};