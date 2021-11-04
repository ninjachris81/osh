#include "systemtimemessage.h"

SystemtimeMessage::SystemtimeMessage(qint64 ts, QObject *parent) : MessageBase(parent), m_ts(ts)
{

}

MessageBase::MESSAGE_TYPE SystemtimeMessage::getMessageType() {
    return MESSAGE_TYPE_SYSTEM_TIME;
}


qlonglong SystemtimeMessage::ts() {
    return m_ts;
}

QString SystemtimeMessage::getFirstLevelId() {
    return "";
}

QString SystemtimeMessage::getSecondLevelId() {
    return "";
}
