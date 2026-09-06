#pragma once

#include "soap/stdsoap2.h"


class AnalyticsServiceWrapper
{
public:
    AnalyticsServiceWrapper(struct soap*);
    int dispatch();
    void deleteObj();
};

