#ifndef OSHSTATECALLBACK_H
#define OSHSTATECALLBACK_H

#include <QObject>
#include "oshcall.h"

class OshStateCallback
{
public:
    virtual void changeState(OshCall::OshCallState newState) = 0;

};

#endif // OSHSTATECALLBACK_H
