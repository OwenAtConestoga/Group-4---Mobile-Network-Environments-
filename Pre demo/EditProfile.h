#pragma once

#include "clientConnection.h"
#include "readDataClient.h"
#include "sendDataClient.h"
#include "LogClass.h"
#include "Password.h"
#include "packet.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

class EditProfile {


public: 

	void editProfile(string, SendDataClient&, ReadDataClient&, LogClass&);

};