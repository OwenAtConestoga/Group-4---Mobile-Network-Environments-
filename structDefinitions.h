#pragma once
#include <iostream>
#include <fstream>
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
    InvalidPacket,
    LogoutPacket,
    ProfileStreamPacket,
    EndOfProfileStreamPacket
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
    string userName;
    string firstName;
    string lastName;
    string bio;
    string userClass;
    int id;
    int voteCount;

    //Initialize all member variables
    Profile() : userName(""), firstName(""), lastName(""), bio(""), userClass(""), id(0), voteCount(0) {}
    Profile(string& filename, bool isFilepath) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        // Assuming each line contains one attribute, separated by a comma
        std::getline(file, userName, ',');
        std::getline(file, firstName, ',');
        std::getline(file, lastName, ',');
        std::getline(file, bio, ',');
        std::getline(file, userClass, ',');

        // Read integers directly from the file
        file >> id;
        file.ignore(); // Ignore the comma
        file >> voteCount;
    }
    Profile(const std::string& formattedString) {
        std::stringstream ss(formattedString);
        std::getline(ss, userName, ',');
        std::getline(ss, firstName, ',');
        std::getline(ss, lastName, ',');
        std::getline(ss, bio, ',');
        std::getline(ss, userClass, ',');
        ss >> id;
        ss.ignore(1); // Ignore the delimiter ','
        ss >> voteCount;
    }
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

struct Account
{
    string username;
    string password;

    Account(): username(""), password("") {}

    operator string() const {
        ostringstream oss;
        oss << username << ',' << password;
        return oss.str();
    }

    Account(const std::string& formattedString) {
        stringstream ss(formattedString);
        getline(ss, username, ',');
        getline(ss, password, ',');
    }

    int size()
    {
        return username.length() + password.length();
    }
};