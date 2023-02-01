#ifndef SERIALIZATIONSUPPORT_H
#define SERIALIZATIONSUPPORT_H

#include <QJsonObject>

#include "sharedlib.h"

class SHARED_LIB_EXPORT SerializationSupport
{
public:
    virtual void serialize(QJsonObject &obj) = 0;

    virtual void deserialize(QJsonObject obj) = 0;

};

#endif // SERIALIZATIONSUPPORT_H
