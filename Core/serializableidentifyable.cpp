#include "serializableidentifyable.h"

QLatin1String SerializableIdentifyable::PROPERTY_ID = QLatin1String("id");
QLatin1String SerializableIdentifyable::PROPERTY_CLASSTYPE = QLatin1String("class_type");
QLatin1String SerializableIdentifyable::PROPERTY_VALUE_GROUP_ID = QLatin1String("value_group_id");

SerializableIdentifyable::SerializableIdentifyable(QString id) : Identifyable(id)
{

}

void SerializableIdentifyable::serialize(QJsonObject &obj) {
    obj.insert(PROPERTY_ID, m_id);
    obj.insert(PROPERTY_CLASSTYPE, getClassName());
}

void SerializableIdentifyable::deserialize(QJsonObject obj) {
    m_id = obj.value(PROPERTY_ID).toString();
}
