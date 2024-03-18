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

void createProfile(ClientConnection &client, const std::string &username){
    std::string firstName, lastName, bio, userClass;
    int id;

    //userName = username;

    std::cout << "Enter Firstname:";
    std::cin >> firstName;

    std::cout << "Enter Lastname:";
    std::cin >> lastName;

    std::cout << "Enter bio:";
    std::cin.ignore();
    std::getline(std::cin, bio);

    std::cout << "Enter Class:";
    std::cin >> userClass;
    
    Packet packet;
    packet.setPacketType(PacketTypes::CreateProfilePacket);

    std::string profileData = username + "," + firstName + "," + lastName+ "," + bio + "," + userClass + ",";

    packet.setData(const_cast<char*>(profileData.c_str()));

    client.sendPacket(packet);

}

bool profileExisted (ClientConnection &client, const std::string &username){
    Packet packet;
    packet.setPacketType(PacketTypes::ProfileRequestPacket);

    packet.setData(const_cast<char*>(username.c_str()));

    client.sendPacket(packet);

    Packet response;
    client.receivePacket(response);

    return response.getPacketType() == PacketTypes::ProfileRequestPacket;
    
}

void editProfile(ClientConnection &client, const std::string &username){
    if(profileExisted(client, username)){
    
        std::string firstName, lastName, bio, userClass;
        int id;
        
        std::cout << "Enter New Firstname:";
        std::cin >> firstName;

        std::cout << "Enter New Lastname:";
        std::cin >> lastName;

        std::cout << "Enter New bio:";
        std::cin.ignore();
        std::getline(std::cin, bio);

        std::cout << "Enter New Class:";
        std::cin >> userClass;
        
        Packet packet;
        packet.setPacketType(PacketTypes::EditProfilePacket);

        std::string profileData = username + "," + firstName + "," + lastName+ "," + bio + "," + userClass + ",";

        packet.setData(const_cast<char*>(profileData.c_str()));

        client.sendPacket(packet);
    }
    else{
        std::cout<<"Profile doesn't exist"<< std::endl;
    }
}

void vote(ClientConnection &client){
    int id = rand()%100;
    std::string str = std::to_string(id);

    Packet packet;
    packet.setPacketType(PacketTypes::VotePacket);

    packet.setData(const_cast<char*>((str.c_str())));
    client.sendPacket(packet);

}

int main(int argc, char* argv[])
{
    ClientConnection client;
    std::string username, password;
   
   

    //get GetUserName
    std::cout << "Enter Username:";
    std::cin >> username;

    std::cout << "Enter Password:";
    std::cin >> password;

    //connect to the server
    if(!client.connectToServer()){
        std::cerr<<"failed to connect to the server" << std::endl;
        return 1;
    }

    //send loging request
    //Password loginCredentials(const_cast<char*>((username+"," + password).c_str()));

    //std::string loginCredentials = username +"," +password;
    //char* credentialsBuffer = new char[loginCredentials.length()+1];
    //strcpy(credentialsBuffer, loginCredentials.c_str());
    //packet.setData(credentialsBuffer);

    //client.sendLoginRequest(loginCredentials);

    PacketTypes responseType = client.receiveLoginResponse();

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

    if(responseType == PacketTypes::LoginSuccessPacket){
        std::cout << "Login successful" << std::endl;
        //add code for other functions( e.g. voting, profile management)
        int choice;

        do{
             std::cout << "1.Create Profile 2.Edit Profile 3.Vote 4. Edit";
             std::cin >> choice;
             switch (choice)
             {
             case 1:
                createProfile(client,username);
                break;

            case 2:
                editProfile(client,username);
                break;

            case 3:
                vote(client);
                break;
             
            case 4:
                break;

            default:
                std::cout<< "Invaild choice" << std::endl;
             }

        }while(choice != 4);
        

    }
    else{
        std::cout << "Loging failed"<< std::endl;
    }

    
    //close the connection
    client.closeConnection();

    return 0;

}