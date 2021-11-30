#include "logmessage.h"
#include "log/logmanager.h"

LogMessage::LogMessage(QString deviceId, QtMsgType logType, QString message, QObject *parent) : MessageBase(parent), m_deviceId(deviceId), m_logType(logType), m_message(message)
{

}

MessageBase::MESSAGE_TYPE LogMessage::getMessageType() {
    return MESSAGE_TYPE_LOG;
}

QString LogMessage::getFirstLevelId() {
    return m_deviceId;
}

QString LogMessage::getSecondLevelId() {
    return LogManager::msgTypeToString(m_logType);
}

QString LogMessage::deviceId() {
    return m_deviceId;
}

QtMsgType LogMessage::logType() {
    return m_logType;
}

QString LogMessage::message() {
    return m_message;
}
