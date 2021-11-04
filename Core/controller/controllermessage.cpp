#include "controllermessage.h"

#include <QDebug>

ControllerMessage::ControllerMessage(QString controllerId, QVariant data, QObject *parent) : MessageBase(parent), m_controllerId(controllerId), m_data(data)
{
    if (m_data.toMap().contains(CONTROLLER_TYPE_ATTR)) {
        m_cmdType = static_cast<CONTROLLER_CMD_TYPE>(m_data.toMap().value(CONTROLLER_TYPE_ATTR).toInt());
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

QVariant ControllerMessage::data() {
    return m_data;
}

CONTROLLER_CMD_TYPE ControllerMessage::cmdType() {
    return m_cmdType;
}
