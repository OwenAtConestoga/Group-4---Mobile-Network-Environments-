#pragma once
#include "structDefinitions.h"
class Vote {
	Profile votedProfile;
public:
	void addVote(int id) {
        int lineNumber = 0;
		std::string dataAsString = checkIDInFile("profile.csv", id, &lineNumber);
		char* data = (char*)calloc(dataAsString.length(), sizeof(char));
		strcpy(data, dataAsString.c_str());
		votedProfile.userName = strtok(data, ",");
		votedProfile.firstName = strtok(NULL, ",");
		votedProfile.lastName = strtok(NULL, ",");
		votedProfile.bio = strtok(NULL, ",");
		votedProfile.userClass = strtok(NULL, ",");
		votedProfile.id = atoi(strtok(NULL, ","));
		votedProfile.voteCount = atoi(strtok(NULL, ","));
        saveInfoToFile("profiles.csv", lineNumber);
	}
    std::string checkIDInFile(const std::string& filename, int searchID, int* lineNumber)
    {
        std::ifstream file(filename);
        std::string line;
        if (!file.is_open()) {
            std::cerr << "Can't Open This File" << std::endl;
            return "-1";
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
                    else {
                        lineNumber++;
                    }
                }
                catch (const std::invalid_argument& ia) {
                    // Ignore if conversion fails
                }
            }
        }

        return "-1"; // Can't find ID
    }
    void saveInfoToFile(const std::string& filename, int skipUntilLine) {
        std::ifstream infile(filename);
        std::string line;
        int lineCount = 0;

        while (std::getline(infile, line) && lineCount < skipUntilLine) {
            lineCount++;
        }
        infile.close();

        if (lineCount < skipUntilLine) {
            std::cerr << "Line number to skip exceeds total lines in the file." << std::endl;
            return;
        }

        std::ofstream file(filename, std::ios_base::app); // Open file in append mode
        if (!file.is_open()) {
            std::cerr << "Can't Open File: " << filename << std::endl;
            return;
        }

        file << votedProfile.userName << ',' << votedProfile.firstName << ',' << votedProfile.lastName << ','
            << votedProfile.bio << ',' << votedProfile.userClass << ',' << votedProfile.id << ',' << votedProfile.voteCount << std::endl;

        file.close(); // Close the file
    }
};