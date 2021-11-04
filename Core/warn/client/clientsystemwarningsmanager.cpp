#include "clientsystemwarningsmanager.h"

#include <QDebug>

#include "warn/systemwarningmessage.h"

#include "macros.h"

QString ClientSystemWarningsManager::MANAGER_NAME = QStringLiteral("ClientSystemWarningsManager");

ClientSystemWarningsManager::ClientSystemWarningsManager(QObject *parent) : ManagerBase(parent)
{

}

void ClientSystemWarningsManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;
    REQUIRE_MANAGER(CommunicationManagerBase);
    REQUIRE_MANAGER(ClientDeviceManager);

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_NAME);
    m_clientDeviceManager = getManager<ClientDeviceManager>(ClientDeviceManager::MANAGER_NAME);
}

QString ClientSystemWarningsManager::getName() {
    return MANAGER_NAME;
}

void ClientSystemWarningsManager::raiseWarning(QString msg) {
    qWarning() << Q_FUNC_INFO << msg;

    if (m_commManager != nullptr) {
        SystemWarningMessage warnMsg(m_clientDeviceManager->device(), msg);
        m_commManager->sendMessage(warnMsg);
    }
}

MessageBase::MESSAGE_TYPE ClientSystemWarningsManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void ClientSystemWarningsManager::handleReceivedMessage(MessageBase* msg) {

}
