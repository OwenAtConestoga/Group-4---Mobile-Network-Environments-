#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <sstream>
#include "structDefinitions.h"


class createProfile
{
    Profile profile;
public:

    // Set up basic initialize the profile with provided data
    createProfile(char* data)
    {
        istringstream dataStream(data);
        getline(dataStream, profile.userName, ',');
        getline(dataStream, profile.firstName, ',');
        getline(dataStream, profile.lastName, ',');
        getline(dataStream, profile.bio, ',');
        getline(dataStream, profile.userClass, ',');
        string idStr, voteCountStr;
        getline(dataStream, idStr, ',');
        profile.id = stoi(idStr);
        getline(dataStream, voteCountStr, ',');
        profile.voteCount = stoi(voteCountStr);
    }

    createProfile(int profileID)
    {
        string dataAsString = checkIDInFile("profile.csv", profileID);
        if (dataAsString.empty())
        {
            std::cerr << "Profile with ID " << profileID << " not found." << std::endl;
            return;
        }
        istringstream dataStream(dataAsString);
        getline(dataStream, profile.userName, ',');
        getline(dataStream, profile.firstName, ',');
        getline(dataStream, profile.lastName, ',');
        getline(dataStream, profile.bio, ',');
        getline(dataStream, profile.userClass, ',');

        string idStr, voteCountStr;
        getline(dataStream, idStr, ',');
        profile.id = stoi(idStr);
        getline(dataStream, voteCountStr, ',');
        profile.voteCount = stoi(voteCountStr);
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
    }

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
            catch (const std::invalid_argument&) {
                continue;
            }
            catch (const std::out_of_range&) {
                continue;
            }
        }

        return "";
    }

    void saveInfoToFile(const std::string& filename) {
        if (checkIDInFile(filename, profile.id) == "") {
            std::ofstream file(filename, std::ios_base::app); // Open file in append mode
            if (!file.is_open()) {
                std::cerr << "Can't Open File: " << filename << std::endl;
                return;
            }

            file << (string)profile + "\n";

            file.close(); // Close the file
        }
    }
};