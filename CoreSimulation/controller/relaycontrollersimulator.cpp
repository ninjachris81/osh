#include "relaycontrollersimulator.h"

#include <QDebug>
#include "controller/controllermanager.h"

RelayControllerSimulator::RelayControllerSimulator(ControllerManager *manager, QString id, quint8 relayCount, QObject *parent) : RelayControllerBase(manager, id, relayCount, parent)
{
    connect(this, &RelayControllerSimulator::controllerConnected, [this] () {
        switchStatusAll(false);
    });
}

void RelayControllerSimulator::switchStatus(quint8 relayIndex, bool status) {
    iDebug() << Q_FUNC_INFO;

    setStatus(relayIndex, status);
}
