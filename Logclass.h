#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include <string>

class LogClass
{
private:
    int totalSize;  // Total size of the log
    std::string fileName;  // Name of the log file

public:
    LogClass(const std::string& fName); // Constructor declaration
    void PrintToFile(const std::string& text); // Write text to log file
    void ReadFile();  // Read and print the log file contents
    int GetTotalSize() const; // Getter for totalSize
};