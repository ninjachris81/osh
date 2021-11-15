#include "relaycontrollerbase.h"

#include <QDebug>
#include "controller/controllermanager.h"

RelayControllerBase::RelayControllerBase(ControllerManager *manager, QString id, quint8 relayCount, QObject *parent) : ControllerBase(manager, id, parent), m_relayCount(relayCount)
{
    m_relayStatus = QBitArray(relayCount, false);

    connect(this, &RelayControllerBase::controllerConnected, [this] () {
        switchStatusAll(false);
    });
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

void RelayControllerBase::switchStatusAll(bool status) {
    for (quint8 i=0;i<m_relayCount;i++) {
        switchStatus(i, status);
    }
}

bool RelayControllerBase::relayStatus(quint8 relayIndex) {
    return m_relayStatus.at(relayIndex);
}

void RelayControllerBase::bindActor(DigitalActor* actor, quint8 relayIndex) {
    QObject::connect(actor, &DigitalActor::valueChanged, [this, actor, relayIndex]() {
        switchStatus(relayIndex, actor->rawValue().toBool());
    });
    m_actorMappings.insert(relayIndex, actor);
}

void RelayControllerBase::bindValueManager(ClientValueManager* clientValueManager) {
    QObject::connect(this, &RelayControllerBase::relayStatusChanged, [this, clientValueManager](quint8 relayIndex) {
        clientValueManager->publishValue(m_actorMappings.value(relayIndex));
    });
}
