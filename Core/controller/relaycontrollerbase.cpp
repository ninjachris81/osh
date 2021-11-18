#include "relaycontrollerbase.h"

#include <QDebug>
#include "controller/controllermanager.h"

RelayControllerBase::RelayControllerBase(ControllerManager *manager, QString id, quint8 relayCount, QObject *parent) : ControllerBase(manager, id, parent), m_relayCount(relayCount)
{
    connect(this, &RelayControllerBase::controllerConnected, [this] () {
        switchStatusAll(false);
    });
}

void RelayControllerBase::setStatus(quint8 relayIndex, bool status) {
    iDebug() << Q_FUNC_INFO << relayIndex << status;
    m_actorMappings.value(relayIndex)->updateValue(status);
}

void RelayControllerBase::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void RelayControllerBase::switchStatusAll(bool status) {
    for (quint8 i=0;i<m_relayCount;i++) {
        switchStatus(i, status);
    }
}

bool RelayControllerBase::relayStatus(quint8 relayIndex) {
    return m_actorMappings.at(relayIndex)->rawValue().toBool();
}

quint8 RelayControllerBase::bindActor(DigitalActor* actor) {
    quint8 relayIndex = m_actorMappings.count();
    m_actorMappings.append(actor);
    QObject::connect(actor, &DigitalActor::statusRequested, [this, relayIndex](bool status) {
        switchStatus(relayIndex, status);
    });
    return relayIndex;
}
