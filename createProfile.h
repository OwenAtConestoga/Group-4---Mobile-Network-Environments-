#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <sstream>
#include "structDefinitions.h"


class createProfile
{
    Profile profile;
    int& TotalSize;
public:

    // Set up basic initialize the profile with provided data
    createProfile(char* data, int& totalsize)
    {
        profile.userName = strtok(data, ",");
        profile.firstName = strtok(NULL, ",");
        profile.lastName = strtok(NULL, ",");
        profile.bio = strtok(NULL, ",");
        profile.userClass = strtok(NULL, ",");
        profile.id = atoi(strtok(NULL, ","));
        profile.voteCount = atoi(strtok(NULL, ","));
        TotalSize = totalsize;
    }

    createProfile(int profileID, int &totalsize)
    {
        std::string dataAsString = checkIDInFile("profile.csv", profileID);
        char* data;
        strcpy(data, dataAsString.c_str());
        profile.userName = strtok(data, ",");
        profile.firstName = strtok(NULL, ",");
        profile.lastName = strtok(NULL, ",");
        profile.bio = strtok(NULL, ",");
        profile.userClass = strtok(NULL, ",");
        profile.id = atoi(strtok(NULL, ","));
        profile.voteCount = atoi(strtok(NULL, ","));
        TotalSize = totalsize;
    }

    createProfile()
    {
        profile.userName = "";
        profile.firstName = "";
        profile.lastName = "";
        profile.bio = "";
        profile.userClass = "";
        profile.id = 0;
        profile.voteCount = 0;
        TotalSize = 0;
    }
    void editProfile(char* data)
    {
        profile.userName = strtok(data, ",");
        profile.firstName = strtok(NULL, ",");
        profile.lastName = strtok(NULL, ",");
        profile.bio = strtok(NULL, ",");
        profile.userClass = strtok(NULL, ",");
        profile.id = atoi(strtok(NULL, ","));
        profile.voteCount = atoi(strtok(NULL, ","));
    }

    void setVoteCount(int newVoteCount) {
        profile.voteCount = newVoteCount;
    }
    int getVoteCount() { return profile.voteCount; }
    std::string getUsername() { return profile.userName;  }
    std::string checkIDInFile(const std::string& filename, int searchID, int* lineNumber = NULL) 
    {
        std::ifstream file(filename);
        std::string line;
        if (!file.is_open()) {
            std::cerr << "Can't Open This File" << std::endl;
            return "-1";
        }
        int* counter;
        if(lineNumber != NULL)
        {
            counter = lineNumber;
        }
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            // Split the line by commas
            while (getline(ss, item, ',')) {
                try {
                    int fileID = std::stoi(item);    // Convert String to Integer
                    if (fileID == searchID) {
                        return line; // Find ID
                    }
                }
                catch (const std::invalid_argument& ia) {
                    // Ignore if conversion fails
                }
            }
        }

        return "-1"; // Can't find ID
    }

    void saveInfoToFile(const std::string& filename) {
        if (checkIDInFile(filename, profile.id) == "-1") {
            std::ofstream file(filename, std::ios_base::app); // Open file in append mode
            if (!file.is_open()) {
                std::cerr << "Can't Open File: " << filename << std::endl;
                return;
            }

            file << profile.userName << ',' << profile.firstName << ',' << profile.lastName << ','
                 << profile.bio << ',' << profile.userClass << ',' << profile.id << ',' << profile.voteCount << std::endl;

            file.close(); // Close the file
        }
    }
};
