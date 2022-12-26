#include "usermanager.h"

#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>

QLatin1String UserManager::MANAGER_ID = QLatin1String("UserManager");

QLatin1String UserManager::USER_TABLE_NAME = QLatin1String("users");

UserManager::UserManager(QObject *parent) : ManagerBase(parent)
{

}

LogCat::LOGCAT UserManager::logCat() {
    return LogCat::ACTOR;
}

void UserManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(DatabaseManager);
    m_databaseManager = getManager<DatabaseManager>(DatabaseManager::MANAGER_ID);

    iDebug() << "Creating user table";
    m_databaseManager->checkCreateTable(USER_TABLE_NAME, 0, QStringList() << User::USER_ID << User::USER_DISPLAY_NAME << User::USER_RIGHTS, QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::StringList);
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

User* UserManager::getUser(QString id) {
    QSqlTableModel userTableModel;
    userTableModel.setTable(USER_TABLE_NAME);
    userTableModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    userTableModel.setFilter(User::USER_ID + "='" + id + "'");
    userTableModel.select();

    /*
    userTableModel.setHeaderData(0, Qt::Horizontal, tr(User::USER_ID.data()));
    userTableModel.setHeaderData(1, Qt::Horizontal, tr(User::USER_DISPLAY_NAME.data()));
    userTableModel.setHeaderData(2, Qt::Horizontal, tr(User::USER_RIGHTS.data()));
    */

    if (userTableModel.rowCount() == 1) {
        User *user = new User(userTableModel.record(0));
        return user;
    } else if (userTableModel.rowCount() == 0) {
        iWarning() << "User not found" << id;
    } else {
        iWarning() << "Multiple users returned";
    }

    return nullptr;
}
