#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")

#include "header.h"
#include "Password.h"

class ClientConnection{

private:
    SOCKET clientSocket;

public:
    ClientConnection(): clientSocket(INVALID_SOCKET){}
    ~ClientConnection(){closeConnection();}


    bool connectToServer();
    void sendLoginRequest(const char* username, const char* password) ;
    PacketTypes receiveLoginResponse();
    void closeConnection();


};
