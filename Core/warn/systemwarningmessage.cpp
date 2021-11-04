#include "systemwarningmessage.h"

SystemWarningMessage::SystemWarningMessage(QString deviceId, QString msg, QObject *parent) : MessageBase(parent), m_deviceId(deviceId), m_msg(msg)
{
}

SystemWarningMessage::SystemWarningMessage(ClientDevice *device, QString msg, QObject *parent) : MessageBase (parent), m_deviceId(device->id()), m_msg(msg) {
}


MessageBase::MESSAGE_TYPE SystemWarningMessage::getMessageType() {
    return MESSAGE_TYPE_SYSTEM_WARNING;
}

QString SystemWarningMessage::deviceId() {
    return m_deviceId;
}

QString SystemWarningMessage::msg() {
    return m_msg;
}

QString SystemWarningMessage::getFirstLevelId() {
    return m_deviceId;
}

QString SystemWarningMessage::getSecondLevelId() {
    return "";
}
