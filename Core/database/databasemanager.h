#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

#include "sharedlib.h"

#include "manager/managerbase.h"

class SHARED_LIB_EXPORT DatabaseManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;
    static QLatin1String DATABASE_TYPE_SQLITE;
    static QLatin1String DATABASE_TYPE_PSQL;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ bool isPriorityManager() override {
        return true;
    }

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    QSqlDatabase* db();

    void checkCreateTable(QString tableName, int primaryKeyColumn, QStringList colNames, QList<QVariant::Type> types);

protected:
    QString getType(QVariant::Type type);

private:
    QSqlDatabase m_db;

signals:

};

#endif // DATABASEMANAGER_H
