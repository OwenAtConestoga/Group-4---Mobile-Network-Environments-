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

enum class ResponseCodes {
    OK, // 200
    ACCEPTED, // 202
    NOCONTENT, // 204
    UNAUTHORIZED, // 401
    NOTFOUND // 404
};

struct Header
{
    PacketTypes packetType;
    int profileLength;
    int acctLength;
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
    int size()
    {
        return userName.length() + firstName.length() + lastName.length()
            + bio.length() + userClass.length() + (sizeof(int) * 2);
    }
};

struct Packet
{
    Header Head;
    unsigned int CRC;
    const unsigned int CONSTCRC = 0xFF00FF00;
};

struct Account
{
    string username;
    string password;

    Account(): username(""), password("") {}

    operator string() const {
        std::ostringstream oss;
        oss << username << ',' << password;
        return oss.str();
    }

    int size()
    {
        return username.length() + password.length();
    }
};