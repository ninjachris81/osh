#pragma once

#include "soap/stdsoap2.h"


class DeviceIOServiceWrapper
{
public:
    DeviceIOServiceWrapper(struct soap*);
    int dispatch();
    void deleteObj();
};

