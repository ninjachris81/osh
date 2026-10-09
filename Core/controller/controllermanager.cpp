#include "controllermanager.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "controllermessage.h"

QLatin1String ControllerManager::MANAGER_ID = QLatin1String("ControllerManager");

ControllerManager::ControllerManager(QObject *parent) : ManagerBase(parent)
{

}

LogCat::LOGCAT ControllerManager::logCat() {
    return LogCat::CONTROLLER;
}

void ControllerManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ControllerBase*> itConfig(m_controllers);
    while(itConfig.hasNext()) {
        itConfig.next();
        itConfig.value()->setConfig(config);
    }

    QMapIterator<QString, ControllerBase*> itInit(m_controllers);
    while(itInit.hasNext()) {
        itInit.next();
        itInit.value()->init();
    }

    REQUIRE_MANAGER(CommunicationManagerBase);
}

void ControllerManager::start() {
    iDebug() << Q_FUNC_INFO;

    CommunicationManagerBase* commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);

    if (commManager->isConnected()) {
        onStart();
    } else {
        iInfo() << "Waiting for communication manager to connect";
    }
    connect(commManager, &CommunicationManagerBase::connected, this, &ControllerManager::onStart);
}

void ControllerManager::onStart() {
    iDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ControllerBase*> itStart(m_controllers);
    while(itStart.hasNext()) {
        itStart.next();
        itStart.value()->start();
    }
}

QString ControllerManager::id() {
    return MANAGER_ID;
}

void ControllerManager::registerController(ControllerBase *controller) {
    if (m_isInitialized) {
        qFatal("Must register controller BEFORE init of manager");
    }

    iDebug() << Q_FUNC_INFO << controller->id();

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
    iDebug() << Q_FUNC_INFO;

    ControllerMessage* controllerMessage = static_cast<ControllerMessage*>(msg);

    if (m_controllers.contains(controllerMessage->controllerId())) {
        m_controllers.value(controllerMessage->controllerId())->handleMessage(controllerMessage);
    } else {
        iWarning() << "Unknown controller" << controllerMessage->controllerId();
    }
}
