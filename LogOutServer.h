#pragma once
#include <iostream>
using namespace std;
class LogOutServer {
	bool isConnection;
	int id;
public:
	void LogOut() {
		isConnection = false;
	}
};