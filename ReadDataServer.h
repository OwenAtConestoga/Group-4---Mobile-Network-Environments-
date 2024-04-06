#pragma once
#include <stdlib.h>
#include "Password.h"
#include "LogOutServer.h"
#include "packet.h"
using namespace std;
class ReadDataServer {
    Password* currentAccount;
public:
    packetClass pktClass;
    LogOutServer LOS;
    string RxBuffer;
    void DeserializeData(char buffer[128]);
    void logFile(string, int);
    int serverFeedBack(ResponseCodes);
    bool canAccessData();
    bool login(Account);
    void LogOut();
};