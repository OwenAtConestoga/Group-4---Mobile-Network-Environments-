#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <cstring>
#include <sstream>
#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 30
using namespace std;

class Password
{
	string username;
	string password;

public:
	Password(char* data)
	{
		istringstream ss(data);
		getline(ss, username, ',');
		getline(ss, password, ',');
	}
	string getUsername() { return username; }
	string getPassword() { return password; }
	bool checkPassword()
	{
		string user, pass;
		if (password.empty() || username.empty())
		{
			return false;
		}
		ifstream file("users.csv");
		char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH];
		string lineAsString;
		while (!file.eof()) {
			file.getline(line, MAX_USERNAME_LENGTH);
			lineAsString = line;
			istringstream ss(lineAsString);
			getline(ss, user, ',');
			getline(ss, pass, ',');
			if (username == user && password == pass){
				return true;
			}
		}
		return false;
	}
};