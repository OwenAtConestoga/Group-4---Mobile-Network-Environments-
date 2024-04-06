#define _CRT_SECURE_NO_WARNINGS

#include "structDefinitions.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

class editProfile
{
    Profile profile;
    bool idExists = false;
    int lineNumber;
    int* TotalSize;
    string fileName;
public:
    editProfile(int profileID, string filename)
    {
        fileName = filename;
        std::string dataAsString = GetDataFromID(profileID);
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
        idExists = true;
    }
    void updateProfile(Profile updatedProfile)
    {
        profile.userName = !updatedProfile.userName.empty() ? updatedProfile.userName : profile.userName;
        profile.firstName = !updatedProfile.firstName.empty() ? updatedProfile.firstName : profile.firstName;
        profile.lastName = !updatedProfile.lastName.empty() ? updatedProfile.lastName : profile.lastName;
        profile.bio = !updatedProfile.bio.empty() ? updatedProfile.bio : profile.bio;
        profile.userClass = !updatedProfile.userClass.empty() ? updatedProfile.userClass : profile.userClass;
        profile.voteCount = updatedProfile.voteCount != 0 ? updatedProfile.voteCount : profile.voteCount;
    }

    void updateFile()
    {
        std::ifstream inFile(fileName); // Open file for reading
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
                lines.push_back((string)profile);
            }
            else {
                lines.push_back(line);
            }
            currentLineNumber++;
        }

        inFile.close();

        // Write the modified content back to the file
        std::ofstream outFile(fileName);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file.\n";
            return;
        }

        for (const auto& line : lines) {
            outFile << line << '\n';
        }

        outFile.close();
    }

    std::string GetDataFromID(int searchID) {
        lineNumber = 0;
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
};