#ifndef SERIALIZABLEIDENTIFYABLE_H
#define SERIALIZABLEIDENTIFYABLE_H

#include "identifyable.h"
#include "datamodel/serializationsupport.h"

class SerializableIdentifyable : public Identifyable, public SerializationSupport
{
public:
    explicit SerializableIdentifyable(QString id = "");

    static QLatin1String PROPERTY_ID;
    static QLatin1String PROPERTY_CLASSTYPE;

    /*virtual*/ void serialize(QJsonObject &obj);

    /*virtual*/ void deserialize(QJsonObject obj);

    virtual QString getClassName() = 0;
};

#endif // SERIALIZABLEIDENTIFYABLE_H
