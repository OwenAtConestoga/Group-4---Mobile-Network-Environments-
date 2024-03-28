#pragma once
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
    static int defaultTotalSize;
public:

    // Set up basic initialize the profile with provided data
    createProfile(char* data, int& totalsize)
        : TotalSize(totalsize)
    {
        std::istringstream dataStream(data);
        std::getline(dataStream, profile.userName, ',');
        std::getline(dataStream, profile.firstName, ',');
        std::getline(dataStream, profile.lastName, ',');
        std::getline(dataStream, profile.bio, ',');
        std::getline(dataStream, profile.userClass, ',');
        std::string idStr, voteCountStr;
        std::getline(dataStream, idStr, ',');
        profile.id = std::stoi(idStr);
        std::getline(dataStream, voteCountStr, ',');
        profile.voteCount = std::stoi(voteCountStr);
    }

    createProfile(int profileID, int& totalsize)
        : TotalSize(totalsize)
    {
        std::string dataAsString = checkIDInFile("profile.csv", profileID);
        if (dataAsString.empty())
        {
            std::cerr << "Profile with ID " << profileID << " not found." << std::endl;
            return;
        }
        std::istringstream dataStream(dataAsString);
        std::getline(dataStream, profile.userName, ',');
        std::getline(dataStream, profile.firstName, ',');
        std::getline(dataStream, profile.lastName, ',');
        std::getline(dataStream, profile.bio, ',');
        std::getline(dataStream, profile.userClass, ',');

        std::string idStr, voteCountStr;
        std::getline(dataStream, idStr, ',');
        profile.id = std::stoi(idStr);
        std::getline(dataStream, voteCountStr, ',');
        profile.voteCount = std::stoi(voteCountStr);
    }

    createProfile() :
        TotalSize(defaultTotalSize)
    {
        profile.userName = "";
        profile.firstName = "";
        profile.lastName = "";
        profile.bio = "";
        profile.userClass = "";
        profile.id = 0;
        profile.voteCount = 0;
    }


    void setVoteCount(int newVoteCount)
    {
        profile.voteCount = newVoteCount;
    }
    int getVoteCount() { return profile.voteCount; }
    std::string getUsername() { return profile.userName; }

    std::string checkIDInFile(const std::string& filename, int searchID) {
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return "";
        }

        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string currentIDStr;
            std::getline(lineStream, currentIDStr, ',');

            try {
                int currentID = std::stoi(currentIDStr);
                if (currentID == searchID) {
                    return line;
                }
            }
            catch (const std::invalid_argument& e) {
                continue;
            }
            catch (const std::out_of_range& e) {
                continue;
            }
        }

        return "";
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
    static int defaultTotalSize;
};
int createProfile::defaultTotalSize = 0;                    // Initialize static member outside the class