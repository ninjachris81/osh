#pragma once

#include "soap/stdsoap2.h"


class MediaServiceWrapper
{
public:
    MediaServiceWrapper(struct soap*);
    int dispatch();
    void deleteObj();
};

