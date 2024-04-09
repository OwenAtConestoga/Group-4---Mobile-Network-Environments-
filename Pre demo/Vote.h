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


class Vote {


public:

	
	void vote(string, SendDataClient&, ReadDataClient&, LogClass&);
    
};