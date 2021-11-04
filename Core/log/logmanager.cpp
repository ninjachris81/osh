#include "logmanager.h"

#include <QDebug>
#include "communication/communicationmanagerbase.h"
#include "macros.h"

QString LogManager::MANAGER_NAME = QStringLiteral("LogManager");

LogManager::LogManager(QObject *parent) : ManagerBase(parent)
{

}

void LogManager::init(LocalConfig *config) {
}

QString LogManager::getName() {
    return MANAGER_NAME;
}

MessageBase::MESSAGE_TYPE LogManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_LOG;
}

void LogManager::handleReceivedMessage(MessageBase* msg) {
    qDebug() << Q_FUNC_INFO;
}
