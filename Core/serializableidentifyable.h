#ifndef SERIALIZABLEIDENTIFYABLE_H
#define SERIALIZABLEIDENTIFYABLE_H

#include "sharedlib.h"

#include "identifyable.h"
#include "datamodel/serializationsupport.h"

class SHARED_LIB_EXPORT SerializableIdentifyable : public Identifyable, public SerializationSupport
{
public:
    explicit SerializableIdentifyable(QString id = "");

    static QLatin1String PROPERTY_ID;
    static QLatin1String PROPERTY_CLASSTYPE;
    static QLatin1String PROPERTY_VALUE_GROUP;

    /*virtual*/ void serialize(QJsonObject &obj);

    /*virtual*/ void deserialize(QJsonObject obj);

    virtual QString getClassName() = 0;
};

#endif // SERIALIZABLEIDENTIFYABLE_H
