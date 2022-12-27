#include "onvifservercontroller.h"
#include <QDebug>

#include "controller/controllermanager.h"

OnvifServerController::OnvifServerController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{

}

void OnvifServerController::init() {
    iDebug() << Q_FUNC_INFO;

    m_onvifServerThread = new OnvifServerThread(m_config->getString(this, "onvif_server.ip", "localhost"), m_config->getInt(this, "onvif_server.port", 8004));
}

void OnvifServerController::start() {
    iDebug() << Q_FUNC_INFO;

    m_onvifServerThread->start();
}

void OnvifServerController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

quint8 OnvifServerController::bindValue(ValueBase *value) {
    return 0;
}
