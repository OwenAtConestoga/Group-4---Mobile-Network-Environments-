#include "ReadDataServer.h"
#include "Logclass.h"
#include <stdlib.h>

ReadDataServer::ReadDataServer(int& Size, Packet newPKT) : TotalSize(Size)
{
    memcpy(&pkt, &newPKT, sizeof(Packet));
    pass = (Password*)calloc(1, sizeof(Password));
}

void ReadDataServer::DeserializeData(char* buffer) 
{
    if (buffer == NULL) 
    {
        std::cerr << "Error: Null buffer pointer." << std::endl;
        return;
    }

    // Copy the header information from buffer to header
    memcpy(&pkt.Head, buffer, sizeof(Header));

    std::string serializedProfile(buffer + sizeof(Header), pkt.Head.Length);
    std::istringstream profileStream(serializedProfile);

    // Extracting profile information from the serialized 
    getline(profileStream, pkt.profile.userName, ',');
    getline(profileStream, pkt.profile.firstName, ',');
    getline(profileStream, pkt.profile.lastName, ',');
    getline(profileStream, pkt.profile.bio, ',');
    getline(profileStream, pkt.profile.userClass, ',');
    std::string idStr, voteCountStr;
    getline(profileStream, idStr, ',');
    getline(profileStream, voteCountStr);
    pkt.profile.id = std::stoi(idStr);
    pkt.profile.voteCount = std::stoi(voteCountStr);

    memcpy(&pkt.CRC, buffer + sizeof(Header) + pkt.Head.Length, sizeof(pkt.CRC));
}

bool ReadDataServer::canAccessData()
{
    return LOS.isLoggedIn();
}

void ReadDataServer::login(char* loginData)
{
    pass = new Password(loginData);
    LOS.Login(pass->getUsername(), pass->checkPassword());
    logFile(serverFeedBack(true));
}

void ReadDataServer::logFile(int serverFeedback)
{
    LogClass* log = new LogClass((string)"log.csv", (int&)TotalSize);
    string toBeLogged = RxBuffer + "| Code: " + to_string(serverFeedback);
    log->PrintToFile(toBeLogged);
    delete log;
}

int ReadDataServer::serverFeedBack(bool successful)
{
    if (successful) {
        return 200;
    }
    return 404;
}
