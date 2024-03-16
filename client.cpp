//Client.cpp
//Matteo Filippone

#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <fstream>
#include <string>
#include "ClientConnection.h"
#include "Password.h"
#include "header.h"





int main(int argc, char* argv[])
{
    ClientConnection client;
    std::string username, password;
   
   

    //get GetUserName
    std::cout << "'Enter Username:";
    std::cin >> username;

    std::cout << "'Enter Password:";
    std::cin >> password;

    

    //send loging request
    //Password loginCredentials(const_cast<char*>((username+"," + password).c_str()));

    //std::string loginCredentials = username +"," +password;
    //char* credentialsBuffer = new char[loginCredentials.length()+1];
    //strcpy(credentialsBuffer, loginCredentials.c_str());
    //packet.setData(credentialsBuffer);

    //client.sendLoginRequest(loginCredentials);

    PacketTypes responseType = client.receiveLoginResponse();

    if(responseType == PacketTypes::LoginSuccessPacket){
        std::cout << "Login successful" << std::endl;
        //add code for other functions( e.g. voting, profile management)
    }
    else{
        std::cout << "Loging failed"<< std::endl;
    }

    // Send login request
    Packet packet;
    packet.setPacketType(PacketTypes::LoginRequestPacket);

    // Concatenate username and password with a delimiter (e.g., ',')
    std::string credentials = username + "," + password;
    char* credentialsBuffer = new char[credentials.length() + 1];
    strcpy(credentialsBuffer, credentials.c_str());

    packet.setData(credentialsBuffer);
    client.sendLoginRequest(username.c_str(), password.c_str());

    delete[] credentialsBuffer;
    
    //connect to the server
    if(!client.connectToServer()){
        std::cerr<<"failed to connect to the server" << std::endl;
        return 1;
    }
    
    //close the connection
    client.closeConnection();

    return 0;

}