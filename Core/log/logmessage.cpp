#include "logmessage.h"

LogMessage::LogMessage(QString deviceId, QString message, QObject *parent) : MessageBase(parent), m_deviceId(deviceId), m_message(message)
{

}

MessageBase::MESSAGE_TYPE LogMessage::getMessageType() {
    return MESSAGE_TYPE_LOG;
}

QString LogMessage::getFirstLevelId() {
    return m_deviceId;
}

QString LogMessage::getSecondLevelId() {
    return "";
}

QString LogMessage::deviceId() {
    return m_deviceId;
}

QString LogMessage::message() {
    return m_message;
}
