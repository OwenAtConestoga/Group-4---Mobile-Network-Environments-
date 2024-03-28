#pragma once
#include <stdlib.h>
#include "Password.h"
#include "LogOutServer.h"
#include "structDefinitions.h"

class ReadDataServer {
    int& TotalSize;
    Packet pkt;
    Password *pass;
    LogOutServer LOS;
public:
    string RxBuffer;
    ReadDataServer(int&, Packet);
    void DeserializeData(char* buffer);
    void logFile(int);
    int serverFeedBack(bool sucessful);
    bool canAccessData();
    void login(char* loginData);
};