#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include <string>

class LogClass
{
private:
    int* TotalSize;  // Total size of the log
    std::string fileName;  // Name of the log file

public:
    LogClass(std::string fName, int &TotalSize); // Constructor declaration
    void PrintToFile(const std::string& text); // Write text to log file
    void ReadFile();  // Read and print the log file contents
};