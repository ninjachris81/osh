#include "clientsystemwarningsmanager.h"

#include <QDebug>

#include "warn/systemwarningmessage.h"

#include "macros.h"

QLatin1Literal ClientSystemWarningsManager::MANAGER_ID = QLatin1Literal("ClientSystemWarningsManager");

ClientSystemWarningsManager::ClientSystemWarningsManager(QObject *parent) : ManagerBase(parent)
{

}

void ClientSystemWarningsManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;
    REQUIRE_MANAGER(CommunicationManagerBase);
    REQUIRE_MANAGER(ClientDeviceDiscoveryManager);

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);
    m_clientDeviceManager = getManager<ClientDeviceDiscoveryManager>(ClientDeviceDiscoveryManager::MANAGER_ID);
}

QString ClientSystemWarningsManager::id() {
    return MANAGER_ID;
}

void ClientSystemWarningsManager::raiseWarning(QString msg) {
    iWarning() << Q_FUNC_INFO << msg;

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
