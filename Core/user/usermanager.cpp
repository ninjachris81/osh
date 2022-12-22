#include "usermanager.h"

#include <QDebug>

QLatin1String UserManager::MANAGER_ID = QLatin1String("UserManager");

UserManager::UserManager(QObject *parent) : ManagerBase(parent)
{

}

LogCat::LOGCAT UserManager::logCat() {
    return LogCat::ACTOR;
}

void UserManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

}

QString UserManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE UserManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void UserManager::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
}
