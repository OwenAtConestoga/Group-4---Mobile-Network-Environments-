#pragma once
#include <iostream>
using namespace std;
class LogOutServer {
	bool isConnection;
	string* userNameLoggedIn;
public:
	void LogOut() {
		isConnection = false;
	}
	void Login(string username, bool success)
	{
		if (success)
		{
			isConnection = success;
			userNameLoggedIn = new string(username);
		}
	}
	bool isLoggedIn()
	{
		return isConnection;
	}
	string currentUser()
	{
		return *userNameLoggedIn;
	}
};