#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include "manager/managerbase.h"

class DatabaseManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    static QLatin1String SIMPLE_STORAGE_TABLE;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ bool isPriorityManager() override {
        return true;
    }

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void simpleSet(QString prefix, QString id, QVariant value);
    QVariant simpleGet(QString prefix, QString id);
    QMap<QString, QVariant> simpleList(QString prefix);
    void simpleRemove(QString prefix, QString id);

protected:
    QSqlDatabase* db();

private:
    QSqlDatabase m_db;

signals:

};

#endif // DATABASEMANAGER_H
