#include "controllermanager.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "controllermessage.h"

QString ControllerManager::MANAGER_NAME = QStringLiteral("ControllerManager");

ControllerManager::ControllerManager(QObject *parent) : ManagerBase(parent)
{

}

void ControllerManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ControllerBase*> it(m_controllers);
    while(it.hasNext()) {
        it.next();
        it.value()->setConfig(config);
    }
}

void ControllerManager::postInit() {
    qDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ControllerBase*> it(m_controllers);
    while(it.hasNext()) {
        it.next();
        it.value()->init();
    }
}

QString ControllerManager::getName() {
    return MANAGER_NAME;
}

void ControllerManager::registerController(ControllerBase *controller) {
    if (m_isInitialized) {
        qFatal("Must register controller BEFORE init of manager");
    }

    qDebug() << Q_FUNC_INFO << controller->id();

    Q_ASSERT(!m_controllers.contains(controller->id()));

    m_controllers.insert(controller->id(), controller);
}

ControllerBase* ControllerManager::getController(QString id) {
    return m_controllers.value(id);
}

QStringList ControllerManager::controllerNames() {
    return m_controllers.keys();
}

MessageBase::MESSAGE_TYPE ControllerManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_CONTROLLER;
}

void ControllerManager::handleReceivedMessage(MessageBase* msg) {
    qDebug() << Q_FUNC_INFO;

    ControllerMessage* controllerMessage = static_cast<ControllerMessage*>(msg);

    if (m_controllers.contains(controllerMessage->controllerId())) {
        m_controllers.value(controllerMessage->controllerId())->handleMessage(controllerMessage);
    } else {
        qWarning() << "Unknown controller" << controllerMessage->controllerId();
    }
}
