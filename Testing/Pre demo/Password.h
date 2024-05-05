#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "structDefinitions.h"
#include <fstream>
#include <cstring>
#include <sstream>
#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 30
using namespace std;

class Password
{
	Account acct;

public:
	Password(Account newAccountDetails)
	{
		acct.username = newAccountDetails.username;
		acct.password = newAccountDetails.password;
	}
	string getUsername() { return acct.username; }
	string getPassword() { return acct.password; }
	bool checkPassword()
	{
		string user, pass;
		if (acct.password.empty() || acct.username.empty())
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
			if (acct.username == user && acct.password == pass){
				return true;
			}
		}
		return false;
	}
};