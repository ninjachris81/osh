#pragma once

#include "soap/stdsoap2.h"

class EventServiceWrapper
{
public:
    EventServiceWrapper(struct soap*);
    int dispatch();
    void deleteObj();
};

