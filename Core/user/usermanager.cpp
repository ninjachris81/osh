#include "usermanager.h"

#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>

QLatin1String UserManager::MANAGER_ID = QLatin1String("UserManager");

UserManager::UserManager(QObject *parent) : ManagerBase(parent)
{

}

LogCat::LOGCAT UserManager::logCat() {
    return LogCat::ACTOR;
}

void UserManager::init(LocalConfig* config) {
    Q_UNUSED(config)
    iDebug() << Q_FUNC_INFO;
}

QString UserManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE UserManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void UserManager::handleReceivedMessage(MessageBase* msg) {
    Q_UNUSED(msg)
    iDebug() << Q_FUNC_INFO;
}

void UserManager::registerUser(OshUser* user) {
    iInfo() << Q_FUNC_INFO;
    m_users.insert(user->id(), user);
}

OshUser* UserManager::user(QString id) {
    return m_users.value(id);
}
