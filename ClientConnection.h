#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")

#include "../Group-4---Mobile-Network-Environments-/header.h"

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

    void sendPacket(Packet &packet);
    void receivePacket(Packet &packet);


};
