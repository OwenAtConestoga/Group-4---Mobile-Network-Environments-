#pragma once
#include <stdlib.h>
#include "structDefinitions.h"

class ReadDataServer {
    int* TotalSize;
    Profile *profile;
    Packet pkt;
public:
    string RxBuffer;
    ReadDataServer(string, int&, Profile, Packet);
    void DeserializeData(char* buffer);
};