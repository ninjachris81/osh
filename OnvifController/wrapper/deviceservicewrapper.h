#pragma once
#include "soap/stdsoap2.h"

class DeviceServiceWrapper
{
public:
    DeviceServiceWrapper(struct soap*);
    int dispatch();
    void deleteObj();
};

