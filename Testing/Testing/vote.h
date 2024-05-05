#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "structDefinitions.h"
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
class Vote {
    Profile votedProfile;
    int lineNumber;
public:
    void addVote(int id) {
        lineNumber = 0;
        std::string dataAsString = GetDataFromID(id, "profiles.csv");

        istringstream dataStream(dataAsString);
        getline(dataStream, votedProfile.userName, ',');
        getline(dataStream, votedProfile.firstName, ',');
        getline(dataStream, votedProfile.lastName, ',');
        getline(dataStream, votedProfile.bio, ',');
        getline(dataStream, votedProfile.userClass, ',');
        string idStr, voteCountStr;
        getline(dataStream, idStr, ',');
        votedProfile.id = stoi(idStr);
        getline(dataStream, voteCountStr, ',');
        votedProfile.voteCount = stoi(voteCountStr);
        votedProfile.voteCount++;
        saveInfoToFile("profiles.csv");
    }
    std::string GetDataFromID(int searchID, string fileName) {
        std::ifstream file(fileName);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << fileName << std::endl;
            return ""; // Return empty string if file cannot be opened
        }

        while (std::getline(file, line)) {
            lineNumber++;
            std::istringstream lineStream(line);
            std::string data;
            int id;

            // Iterate over each delimiter in the line
            while (std::getline(lineStream, data, ',')) {
                try {
                    id = std::stoi(data); // Convert data to integer
                    if (id == searchID) {
                        return line; // Return the entire line if ID matches
                    }
                }
                catch (const std::invalid_argument&) {
                    continue; // Skip if data cannot be converted to integer
                }
            }
        }

        return ""; // Return empty string if ID not found
    }
    void saveInfoToFile(const std::string& filename) {
        std::ifstream inFile(filename); // Open file for reading
        if (!inFile.is_open()) {
            std::cerr << "Error opening file.\n";
            return;
        }

        std::vector<std::string> lines;
        std::string line;
        int currentLineNumber = 1;

        // Read each line from the file and store it in a vector
        while (std::getline(inFile, line)) {
            if (currentLineNumber == lineNumber) {
                // Replace the content of the line at the specified line number
                lines.push_back((string)votedProfile);
            }
            else {
                lines.push_back(line);
            }
            currentLineNumber++;
        }

        inFile.close();

        // Write the modified content back to the file
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file.\n";
            return;
        }

        for (const auto& line : lines) {
            outFile << line << '\n';
        }

        outFile.close();
    }
};