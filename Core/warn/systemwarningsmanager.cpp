#include "systemwarningsmanager.h"

#include <QDebug>

QString SystemWarningsManager::MANAGER_NAME = QStringLiteral("SystemWarningsManager");

SystemWarningsManager::SystemWarningsManager(QObject *parent) : ManagerBase(parent)
{

}

void SystemWarningsManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;
}

QString SystemWarningsManager::getName() {
    return MANAGER_NAME;
}

MessageBase::MESSAGE_TYPE SystemWarningsManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_SYSTEM_WARNING;
}

void SystemWarningsManager::handleReceivedMessage(MessageBase* msg) {

}
