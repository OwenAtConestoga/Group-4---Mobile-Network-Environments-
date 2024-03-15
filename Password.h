#pragma once
#include <fstream>
#include <string>
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
		username = strtok(data, ",");
		password = strtok(NULL, ",");
	}
	string getUsername() { return username; }
	string getPassword() { return password; }
	bool checkPassword(string usernameChecked)
	{
		if (password.empty() || username.empty() || !username._Equal(usernameChecked))
		{
			return false;
		}
		ifstream file("users.csv");
		char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH];
		while (!file.eof()) {
			file.getline(line, MAX_USERNAME_LENGTH);
			char* token = strtok(line, ",");
			char* pass = strtok(NULL, ",");
			if (strcmp(token, username.c_str()) == 0) 
			{
				if (strcmp(pass, password.c_str()) == 0)
				{
					return true;
				}
				break;
			}
		}
		return false;
	}
};