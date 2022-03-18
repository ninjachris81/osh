#include "serializableidentifyable.h"

QLatin1String SerializableIdentifyable::PROPERTY_ID = QLatin1String("id");
QLatin1String SerializableIdentifyable::PROPERTY_CLASSTYPE = QLatin1String("classType");

SerializableIdentifyable::SerializableIdentifyable(QString id, QObject* parent) : Identifyable(id, parent)
{

}

void SerializableIdentifyable::serialize(QJsonObject &obj) {
    obj.insert(PROPERTY_ID, m_id);
    obj.insert(PROPERTY_CLASSTYPE, metaObject()->className());
}

void SerializableIdentifyable::deserialize(QJsonObject obj) {
    m_id = obj.value(PROPERTY_ID).toString();
}
