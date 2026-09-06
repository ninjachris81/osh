#pragma once

#include <QObject>
#include "oshcall.h"

class OshStateCallback
{
public:
    virtual void changeState(OshCall::OshCallState newState) = 0;

};

