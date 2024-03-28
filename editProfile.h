#include "structDefinitions.h"
#include <string>
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
    editProfile(int profileID, int& totalsize, string filename)
    {
        fileName = filename;
        std::string dataAsString = GetDataFromID(profileID);
        if (dataAsString == "")
        {
            return;
        }
        char* data = (char*)calloc(1, sizeof(char) * dataAsString.length());
        strcpy(data, dataAsString.c_str());
        profile.userName = strtok(data, ",");
        profile.firstName = strtok(NULL, ",");
        profile.lastName = strtok(NULL, ",");
        profile.bio = strtok(NULL, ",");
        profile.userClass = strtok(NULL, ",");
        profile.id = atoi(strtok(NULL, ","));
        profile.voteCount = atoi(strtok(NULL, ","));
        TotalSize = (int*)totalsize;
        idExists == true;
    }
    void updateProfile(char* username = NULL, char* firstname = NULL, char* lastname = NULL, char* bio = NULL, char* userclass = NULL, int voteCount = NULL)
    {
        profile.userName = username ? username:profile.userName;
        profile.firstName = firstname ? firstname : profile.firstName;
        profile.lastName = lastname ? lastname : profile.lastName;
        profile.bio = bio ? bio : profile.bio;
        profile.userClass = userclass ? userclass : profile.userClass;
        profile.voteCount = voteCount ? voteCount : profile.voteCount;
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
};