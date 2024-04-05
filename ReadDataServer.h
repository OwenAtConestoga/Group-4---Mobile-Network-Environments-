#pragma once
#include <stdlib.h>
#include "Password.h"
#include "LogOutServer.h"
#include "packet.h"

class ReadDataServer {
    int& TotalSize;
    Password* currentAccount;
public:
    packetClass pktClass;
    LogOutServer LOS;
    string RxBuffer;

    void DeserializeData(char* buffer);
    void logFile(string, int);
    int serverFeedBack(ResponseCodes);
    bool canAccessData();
    bool login(Account);
    void LogOut();
};