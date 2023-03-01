#include "messagebase.h"

MessageBase::MessageBase(QObject *parent) : QObject(parent)
{

}

QString MessageBase::senderDeviceId() {
    return m_senderDeviceId;
}

qint64 MessageBase::ts() {
    return m_ts;
}

void MessageBase::setSenderDeviceId(QString senderDeviceId) {
    m_senderDeviceId = senderDeviceId;
}

void MessageBase::setTs(qint64 ts) {
    m_ts = ts;
}
