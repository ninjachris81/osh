#include "valuemessage.h"

ValueMessage::ValueMessage(QString valueGroupId, QString valueId, QVariant rawValue, QObject *parent) : MessageBase(parent), m_valueGroupId(valueGroupId), m_valueId(valueId), m_rawValue(rawValue)
{
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

