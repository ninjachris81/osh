#include "databasemanager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDataStream>
#include <QSqlRecord>

QLatin1String DatabaseManager::MANAGER_ID = QLatin1String("DatabaseManager");
QLatin1String DatabaseManager::DATABASE_TYPE_SQLITE = QLatin1String("QSQLITE");
QLatin1String DatabaseManager::DATABASE_TYPE_PSQL = QLatin1String("QPSQL");


DatabaseManager::DatabaseManager(QObject *parent)
    : ManagerBase(parent)
{

}

QSqlDatabase* DatabaseManager::db() {
    return &m_db;
}

void DatabaseManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    QString databaseType = config->getString("database.type", DATABASE_TYPE_SQLITE);
    if (databaseType == DATABASE_TYPE_SQLITE) {
        m_db = QSqlDatabase::addDatabase(DATABASE_TYPE_SQLITE);
        m_db.setDatabaseName(config->getString("database.name", "database.db"));
    } else if (databaseType == DATABASE_TYPE_PSQL) {
        m_db = QSqlDatabase::addDatabase(DATABASE_TYPE_PSQL);
        m_db.setDatabaseName(config->getString("database.name", "osh"));
        m_db.setHostName(config->getString("database.host", "localhost"));
        m_db.setPort(config->getInt("database.port", 5432));
        m_db.setUserName(config->getString("database.username", "osh"));
        m_db.setPassword(config->getString("database.password", "osh"));
    }

    if (m_db.open()) {
        iInfo() << "Opened database" << m_db.databaseName();
    } else {
        iWarning() << m_db.databaseName() << m_db.lastError();
        qFatal("Failed to open database");
    }
}

QString DatabaseManager::id() {
    return MANAGER_ID;
}

void DatabaseManager::checkCreateTable(QString tableName, int primaryKeyColumn, QStringList colNames, QList<QVariant::Type> types) {
    iInfo() << Q_FUNC_INFO << tableName;

    Q_ASSERT(colNames.size() == types.size());
    Q_ASSERT(!tableName.isEmpty());

    QString sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";

    for (uint8_t i = 0;i< colNames.size();i++) {
        if (i > 0) {
            sql.append(", ");
        }
        sql.append(colNames.at(i));
        sql.append(" ");
        sql.append(getType(types.at(i)));
        if (primaryKeyColumn == i) {
            sql.append(" PRIMARY KEY");
        }
    }

    sql.append(")");

    QSqlQuery query(m_db);

    iDebug() << sql;

    if (query.prepare(sql)) {
        if (query.exec()) {
            iInfo() << "Table created";
        } else {
            iWarning()  << "Failed to prepare statement" << query.lastError();
        }
    } else {
        iWarning() << "Failed to prepare statement" << query.lastError();
    }
}

QString DatabaseManager::getType(QVariant::Type type) {
    switch(type) {
    case QVariant::String:
        return "varchar(255)";
    case QVariant::StringList:
        return "text";
    default:
         qFatal("Unsupported data type");
    }
}

MessageBase::MESSAGE_TYPE DatabaseManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void DatabaseManager::handleReceivedMessage(MessageBase* msg) {

}
