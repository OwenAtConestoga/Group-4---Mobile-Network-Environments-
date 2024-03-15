#pragma once
#include <string>
#include <fstream>
#include <iostream>


class Profile
{
    // Basic Account setting
    std::string userName;
    std::string firstName;
    std::string lastName;
    std::string bio;
    std::string userClass;
    int id;
    int voteCount;
public:

    // Set up basic initialize the profile with provided data
    Profile(char* data)
    {
        userName = strtok(data, ",");
        firstName = strtok(NULL, ",");
        lastName = strtok(NULL, ",");
        bio = strtok(NULL, ",");
        userClass = strtok(NULL, ",");
        id = atoi(strtok(NULL, ","));
        voteCount = atoi(strtok(NULL, ","));
    }

    Profile(int profileID)
    {
        ifstream file("profile.csv");
        char* data; // need to add function to retrieve data based off of id
        userName = strtok(data, ",");
        firstName = strtok(NULL, ",");
        lastName = strtok(NULL, ",");
        bio = strtok(NULL, ",");
        userClass = strtok(NULL, ",");
        id = atoi(strtok(NULL, ","));
        voteCount = atoi(strtok(NULL, ","));
    }

    void editProfile(char* data)
    {
        userName = strtok(data, ",");
        firstName = strtok(NULL, ",");
        lastName = strtok(NULL, ",");
        bio = strtok(NULL, ",");
        userClass = strtok(NULL, ",");
        id = atoi(strtok(NULL, ","));
        voteCount = atoi(strtok(NULL, ","));
    }
    void setVoteCount(int newVoteCount) {
        voteCount = newVoteCount;
    }
    int getVoteCount() { return voteCount; }
    string getUsername() { return userName;  }
};
