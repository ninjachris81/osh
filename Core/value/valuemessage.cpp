#include "valuemessage.h"

#include "shared/mqtt_qt.h"

ValueMessage::ValueMessage(QString valueGroupId, QString valueId, QVariant rawValue, QObject *parent) : MessageBase(parent), m_valueGroupId(valueGroupId), m_valueId(valueId), m_rawValue(rawValue)
{
}

ValueMessage::ValueMessage(QString valueGroupId, QString valueId, QVariantMap value, QObject *parent) : MessageBase(parent), m_valueGroupId(valueGroupId), m_valueId(valueId)
{
    if (value.contains(MQTT_SINGLE_VALUE_ATTR)) {
        m_rawValue = value.value(MQTT_SINGLE_VALUE_ATTR);
    }
}

MessageBase::MESSAGE_TYPE ValueMessage::getMessageType() {
    return MESSAGE_TYPE_VALUE;
}

QString ValueMessage::getFirstLevelId() {
    return m_valueGroupId;
}

QString ValueMessage::getSecondLevelId() {
    return m_valueId;
}

QString ValueMessage::valueGroupId() {
    return m_valueGroupId;
}

QString ValueMessage::valueId() {
    return m_valueId;
}

QVariant ValueMessage::rawValue() {
    return m_rawValue;
}

