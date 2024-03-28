#pragma once
#include "structDefinitions.h"
#include <vector>
class Vote {
	Profile votedProfile;
    int lineNumber;
public:
	void addVote(int id) {
        lineNumber = 0;
		std::string dataAsString = GetDataFromID("profile.csv", id);

		char* data = (char*)calloc(dataAsString.length(), sizeof(char));
		strcpy(data, dataAsString.c_str());
		votedProfile.userName = strtok(data, ",");
		votedProfile.firstName = strtok(NULL, ",");
		votedProfile.lastName = strtok(NULL, ",");
		votedProfile.bio = strtok(NULL, ",");
		votedProfile.userClass = strtok(NULL, ",");
		votedProfile.id = atoi(strtok(NULL, ","));
		votedProfile.voteCount = atoi(strtok(NULL, ","));
        saveInfoToFile("profiles.csv");
	}
    std::string GetDataFromID(const std::string& fileName, int searchID) {
        lineNumber = 0;
        std::ifstream file(fileName);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << fileName << std::endl;
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
                lineNumber++;
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