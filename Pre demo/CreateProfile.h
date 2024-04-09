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


class CreateProfile {
private:

public:
    
    void createProfile(string, SendDataClient&, ReadDataClient&, LogClass&);

};