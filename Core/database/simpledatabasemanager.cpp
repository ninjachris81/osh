#include "simpledatabasemanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDataStream>

#include "macros.h"
#include "qjsonvalue.h"

QLatin1String SimpleDatabaseManager::SIMPLE_STORAGE_TABLE = QLatin1String("simple_storage");
QLatin1String SimpleDatabaseManager::MANAGER_ID = QLatin1String("SimpleDatabaseManager");

SimpleDatabaseManager::SimpleDatabaseManager(QObject *parent) : ManagerBase(parent)
{

}

void SimpleDatabaseManager::init(LocalConfig *config) {
    Q_UNUSED(config)

    REQUIRE_MANAGER(DatabaseManager);

    m_databaseManager = getManager<DatabaseManager>(DatabaseManager::MANAGER_ID);

    QSqlQuery query(*m_databaseManager->db());
    if (!query.exec("CREATE TABLE IF NOT EXISTS " + SIMPLE_STORAGE_TABLE + " (id TEXT PRIMARY KEY, value TEXT)")) {
        iWarning() << "Failed to execute statement" << query.lastError();
    }
}

QString SimpleDatabaseManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE SimpleDatabaseManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void SimpleDatabaseManager::handleReceivedMessage(MessageBase* msg) {
    Q_UNUSED(msg)
}

void SimpleDatabaseManager::simpleSet(QString prefix, QString id, QVariant value) {
    QSqlQuery query(*m_databaseManager->db());
    query.prepare("INSERT INTO " + SIMPLE_STORAGE_TABLE + " (id, value) VALUES (:id, :value) ON CONFLICT(id) DO UPDATE SET value = :value");
    query.bindValue(":id", prefix + "_" + id);
    query.bindValue(":value", value);

    if (!query.exec()) {
        iWarning() << "Failed to execute statement" << query.lastError();
    }
}

QVariant SimpleDatabaseManager::simpleGet(QString prefix, QString id, QVariant::Type expectedType) {
    QSqlQuery query(*m_databaseManager->db());
    query.prepare("SELECT value FROM " + SIMPLE_STORAGE_TABLE + " WHERE id = :id");
    query.bindValue(":id", prefix + "_" + id);

    if (query.exec()) {
        if (query.next()) {
            QVariant returnVal = query.value(0);

            if (returnVal.type() != expectedType) {
                iWarning() << "Trying to convert stored value";
                returnVal.convert(expectedType);
            }

            return returnVal;
        } else {
            // no value stored yet
        }
    } else {
        iWarning() << "Failed to execute statement" << query.lastError();
    }

    return QVariant();
}

QMap<QString, QVariant> SimpleDatabaseManager::simpleList(QString prefix) {
    QSqlQuery query(*m_databaseManager->db());
    query.prepare("SELECT id, value FROM " + SIMPLE_STORAGE_TABLE + " WHERE id LIKE :id");
    query.bindValue(":id", prefix + "_%");

    if (query.exec()) {
        QMap<QString, QVariant> returnList;
        while (query.next()) {
            QByteArray data = query.value(1).toByteArray();
            QDataStream ds(&data,QIODevice::ReadOnly);
            QVariant val;
            ds >> val;
            returnList.insert(query.value(0).toString().mid(prefix.length()+1), val);
        }

        return returnList;
    } else {
        iWarning() << "Failed to execute statement" << query.lastError();
    }

    return QMap<QString, QVariant>();
}

void SimpleDatabaseManager::simpleRemove(QString prefix, QString id) {
    QSqlQuery query(*m_databaseManager->db());
    query.prepare("DELETE FROM " + SIMPLE_STORAGE_TABLE + " WHERE id = :id");
    query.bindValue(":id", prefix + "_" + id);

    if (!query.exec()) {
        iWarning() << "Failed to remove entry" << prefix << id << query.lastError();
    }
}
