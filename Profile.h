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
    Profile() 
    {
        userName = "";
        firstName = "";
        lastName = "";
        bio = "";
        userClass = "";
        id = NULL;
        voteCount = 0;

    }
    // Set up basic initialize the profile with provided data
    Profile(char* data)
    {
        char* token = strtok(data, ",");
        userName = strtok(NULL, ",");
        firstName = strtok(NULL, ",");
        lastName = strtok(NULL, ",");
        bio = strtok(NULL, ",");
        userClass = strtok(NULL, ",");
        id = atoi(strtok(NULL, ","));
        voteCount = atoi(strtok(NULL, ","));
    }
    void editProfile(char* data)
    {
        char* token = strtok(data, ",");
        userName = strtok(NULL, ",");
        firstName = strtok(NULL, ",");
        lastName = strtok(NULL, ",");
        bio = strtok(NULL, ",");
        userClass = strtok(NULL, ",");
        id = atoi(strtok(NULL, ","));
        voteCount = atoi(strtok(NULL, ","));
    }
};
