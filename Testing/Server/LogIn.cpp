// Log in Class
// Matteo Filippone

#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")
#include <string>
#include <iostream>
#include <fstream>

class LogIn{

struct User
{
    std::string userName;
    std::string password;

}user;

struct User getUser(){

    User user;

    std::cout << "Client User Log In" << std::endl;

    std::cout << "Enter User Name: ";
    std::cin >> user.userName;

    std::cout << "Enter Password: ";
    std::cin >> user.password;

    return user;

}

void checkUser(std::string name, std::string pass){

std::ifstream file("users.csv");

    if(file.is_open()){



    }

    else {
        std::cout << "Unable to open file" << std::endl;
    }

}


}