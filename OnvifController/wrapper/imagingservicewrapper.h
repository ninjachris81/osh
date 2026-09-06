#pragma once

#include "soap/stdsoap2.h"


class ImagingServiceWrapper
{
public:
    ImagingServiceWrapper(struct soap*);
    int dispatch();
    void deleteObj();
};

