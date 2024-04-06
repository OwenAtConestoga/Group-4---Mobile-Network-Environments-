#include "ReadDataServer.h"
#include "Logclass.h"
#include <stdlib.h>
void ReadDataServer::DeserializeData(char buffer[128]) {
    if (buffer == nullptr) {
        std::cerr << "Error: Null buffer pointer." << std::endl;
        return;
    }

    // Initialize offset
    int offset = 0;

    // Copy the header information from buffer to header
    memcpy(&pktClass.Head, buffer + offset, sizeof(Header));
    offset += sizeof(Header);

    // Copy the profile data from buffer to profile
    if (pktClass.Head.profileLength > 0) {
        string profileAsString(buffer + offset, pktClass.Head.profileLength);
        pktClass.profile = Profile(profileAsString);
        offset += pktClass.Head.profileLength;
    }

    // Copy the account data from buffer to loginInfo
    if (pktClass.Head.acctLength > 0) {
        string acctAsString(buffer + offset, pktClass.Head.acctLength);
        pktClass.loginInfo = Account(acctAsString);
        offset += pktClass.Head.profileLength;
    }
    else {
        pktClass.loginInfo.username = "";
        pktClass.loginInfo.password = "";
    }

    // Copy CRC from buffer to pktClass.CRC
    memcpy(&pktClass.CRC, buffer + offset, sizeof(unsigned int));
    offset += sizeof(unsigned int);
}




bool ReadDataServer::canAccessData()
{
    return LOS.isLoggedIn();
}

void ReadDataServer::logFile(string info, int serverFeedback)
{
    LogClass* log = new LogClass((string)"log.csv");
    string toBeLogged = "Response: " + to_string(serverFeedback);
    log->PrintToFile(info + toBeLogged + "\n\n");
    delete log;
}

int ReadDataServer::serverFeedBack(ResponseCodes Code)
{
    switch (Code) {
    case(ResponseCodes::OK):
        return 200;
        break;
    case(ResponseCodes::ACCEPTED):
        return 202;
        break;
    case(ResponseCodes::NOCONTENT):
        return 204;
        break;
    case(ResponseCodes::UNAUTHORIZED):
        return 401;
        break;
    case(ResponseCodes::NOTFOUND):
        return 404;
        break;
    default:
        return 0;
    }
}

bool ReadDataServer::login(Account acct)
{
    currentAccount = new Password(acct);
    LOS.Login(currentAccount->getUsername(), currentAccount->checkPassword());
    logFile("--Login Attempt--\n", serverFeedBack(ResponseCodes::OK));
    return LOS.isLoggedIn();
}
void ReadDataServer::LogOut()
{
    LOS.LogOut();
    delete currentAccount;
}