#include "databasemanager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDataStream>
#include <QSqlRecord>

QLatin1String DatabaseManager::MANAGER_ID = QLatin1String("DatabaseManager");
QLatin1String DatabaseManager::SIMPLE_STORAGE_TABLE = QLatin1String("simple_storage");

DatabaseManager::DatabaseManager(QObject *parent)
    : ManagerBase(parent)
{

}

QSqlDatabase* DatabaseManager::db() {
    return &m_db;
}

void DatabaseManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(config->getString("database.name", "database.db"));
    if (m_db.open()) {
        m_db.exec("CREATE TABLE IF NOT EXISTS " + SIMPLE_STORAGE_TABLE + " (id TEXT PRIMARY KEY, value BLOB)");
    } else {
        iWarning() << "Failed to open database" << m_db.databaseName() << m_db.lastError();
    }
}

QString DatabaseManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE DatabaseManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void DatabaseManager::handleReceivedMessage(MessageBase* msg) {

}

void DatabaseManager::simpleSet(QString prefix, QString id, QVariant value) {
    QByteArray data;
    QDataStream ds(&data,QIODevice::WriteOnly);
    ds << value;

    QSqlQuery query(m_db);
    query.prepare("INSERT OR REPLACE INTO " + SIMPLE_STORAGE_TABLE + " (id, value) VALUES (:id, :value)");
    query.bindValue(":id", prefix + "_" + id);
    query.bindValue(":value", data);

    if (!query.exec()) {
        iWarning() << "Failed to execute statement" << query.lastError();
    }
}

QVariant DatabaseManager::simpleGet(QString prefix, QString id) {
    QSqlQuery query(m_db);
    query.prepare("SELECT value FROM " + SIMPLE_STORAGE_TABLE + " WHERE id = :id");
    query.bindValue(":id", prefix + "_" + id);

    if (query.exec()) {
        if (query.next()) {
            QByteArray data = query.value(0).toByteArray();
            QDataStream ds(&data,QIODevice::ReadOnly);
            QVariant returnVal;
            ds >> returnVal;
            return returnVal;
        } else {
            // no value stored yet
        }
    } else {
        iWarning() << "Failed to execute statement" << query.lastError();
    }

    return QVariant();
}

QMap<QString, QVariant> DatabaseManager::simpleList(QString prefix) {
    QSqlQuery query(m_db);
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

void DatabaseManager::simpleRemove(QString prefix, QString id) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM " + SIMPLE_STORAGE_TABLE + " WHERE id = :id");
    query.bindValue(":id", prefix + "_" + id);

    if (!query.exec()) {
        iWarning() << "Failed to remove entry" << prefix << id << query.lastError();
    }
}
