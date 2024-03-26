#include "LogClass.h"

LogClass::LogClass(const std::string& fName) : fileName(fName), totalSize(0) {}

// Write text to log file and update totalSize
void LogClass::PrintToFile(const std::string& text)
{
    std::ofstream outFile(fileName, std::ios::app);
    if (outFile.is_open())
    {
        outFile << text << std::endl;
        totalSize += text.size() + 1;
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


int LogClass::GetTotalSize() const
{
    return totalSize;// Get totalSize
}