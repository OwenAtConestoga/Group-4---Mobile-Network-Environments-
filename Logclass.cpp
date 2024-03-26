#include "LogClass.h"

LogClass::LogClass(std::string fName, int &totalsize) : fileName(fName), TotalSize((int*)&totalsize) {}

// Write text to log file and update totalSize
void LogClass::PrintToFile(const std::string& text)
{
    std::ofstream outFile(fileName, std::ios::app);
    if (outFile.is_open())
    {
        outFile << text << std::endl;
        TotalSize += text.size() + 1;
        outFile.close();
    }
    else
    {
        std::cerr << "Could not open file: " << fileName << std::endl;
    }
}

// Read and print the log file contents
void LogClass::ReadFile()
{
    std::ifstream inFile(fileName);
    std::string line;
    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            std::cout << line << std::endl;
        }
        inFile.close();
    }
    else
    {
        std::cerr << "Could not read file: " << fileName << std::endl;
    }
}