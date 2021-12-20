#include "systemwarningsmanager.h"

#include <QDebug>

QLatin1String SystemWarningsManager::MANAGER_ID = QLatin1String("SystemWarningsManager");

SystemWarningsManager::SystemWarningsManager(QObject *parent) : ManagerBase(parent)
{

}

void SystemWarningsManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;
}

QString SystemWarningsManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE SystemWarningsManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_SYSTEM_WARNING;
}

void SystemWarningsManager::handleReceivedMessage(MessageBase* msg) {

}
