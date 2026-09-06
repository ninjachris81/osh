#pragma once

#include "soap/stdsoap2.h"


class PTZServiceWrapper
{
public:
    PTZServiceWrapper(struct soap*);
    int dispatch();
    void deleteObj();
};

