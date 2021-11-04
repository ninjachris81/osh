#include "relaycontrollerbase.h"

#include <QDebug>

RelayControllerBase::RelayControllerBase(ControllerManager *manager, QString id, quint8 relayCount, QObject *parent) : ControllerBase(manager, id, parent), m_relayCount(relayCount)
{
    m_relayStatus = QBitArray(relayCount, false);
}

void RelayControllerBase::setStatus(quint8 relayIndex, bool status) {
    if (m_relayStatus.at(relayIndex) != status) {
        qDebug() << Q_FUNC_INFO << relayIndex << status;

        m_relayStatus.setBit(relayIndex, status);
        Q_EMIT(relayStatusChanged(relayIndex));
    }
}

void RelayControllerBase::handleMessage(ControllerMessage *msg) {
    qDebug() << Q_FUNC_INFO << msg->cmdType();
}
