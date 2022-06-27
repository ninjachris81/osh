#include "controllermessage.h"

#include <QDebug>

ControllerMessage::ControllerMessage(QString controllerId, QVariantMap data, QObject *parent) : MessageBase(parent), m_controllerId(controllerId), m_data(data)
{
    if (m_data.contains(CONTROLLER_TYPE_ATTR)) {
        m_cmdType = static_cast<ControllerBase::CONTROLLER_CMD_TYPE>(m_data.value(CONTROLLER_TYPE_ATTR).toInt());
    } else {
        qWarning() << "Invalid controller data" << m_data;
    }
}

MessageBase::MESSAGE_TYPE ControllerMessage::getMessageType() {
    return MESSAGE_TYPE_CONTROLLER;
}

QString ControllerMessage::getFirstLevelId() {
    return m_controllerId;
}

QString ControllerMessage::getSecondLevelId() {
    return "";
}

QString ControllerMessage::controllerId() {
    return m_controllerId;
}

QVariantMap ControllerMessage::data() {
    return m_data;
}

ControllerBase::CONTROLLER_CMD_TYPE ControllerMessage::cmdType() {
    return m_cmdType;
}
