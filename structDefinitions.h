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

class Packet 
{
public:
    Header Head;
    string dataField;
    Profile profile;
    unsigned int CRC;
    static const unsigned int CONSTCRC = 0xFF00FF00;

    Packet() : CRC(0) {}

    // directly manipulating Packet members to support struct-like usage
    void setHeader(const Header& header) { Head = header; }
    Header getHeader() const { return Head; }

    void setDataField(const string& data) { dataField = data; }
    string getDataField() const { return dataField; }

    void setProfile(const Profile& p) { profile = p; }
    Profile getProfile() const { return profile; }

    void setCRC(unsigned int crc) { CRC = crc; }
    unsigned int getCRC() const { return CRC; }

};