#pragma once
#include <iostream>
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
};

struct Packet 
{
    Header Head;
    string dataField;
    unsigned int CRC;
    const unsigned int CONSTCRC = 0xFF00FF00;
};