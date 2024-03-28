#include "ReadDataServer.h"
#include "Logclass.h"
#include <stdlib.h>

ReadDataServer::ReadDataServer(int& Size, Packet newPKT) : TotalSize(Size)
{
    memcpy(&pkt, &newPKT, sizeof(Packet));
}

void ReadDataServer::DeserializeData(char* buffer) {
    if (buffer == NULL) {
        std::cerr << "Error: Null buffer pointer." << std::endl;
        return;
    }
    // Copy the header information from buffer to header
    memcpy(&pkt.Head, buffer, sizeof(Header));

    // Allocate memory for dataField based on header.Length
    pkt.dataField = new char[pkt.Head.Length];

    // Copy the body from buffer to dataField
    memcpy(&pkt.dataField, buffer + sizeof(Header), pkt.Head.Length);

    // Copy the CRC from buffer to CRC
    memcpy(&pkt.CRC, buffer + sizeof(Header) + pkt.Head.NumOfBytes, sizeof(pkt.CRC));
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
    delete[] log;
}

int ReadDataServer::serverFeedBack(bool successful)
{
    if (successful) {
        return 200;
    }
    return 404;
}
