#ifndef SIMPLEDATABASEMANAGER_H
#define SIMPLEDATABASEMANAGER_H

#include <QObject>
#include "manager/managerbase.h"

#include "database/databasemanager.h"
#include "sharedlib.h"

class SHARED_LIB_EXPORT SimpleDatabaseManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit SimpleDatabaseManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    static QLatin1String SIMPLE_STORAGE_TABLE;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void simpleSet(QString prefix, QString id, QVariant value);
    QVariant simpleGet(QString prefix, QString id, QVariant::Type expectedType);
    QMap<QString, QVariant> simpleList(QString prefix);
    void simpleRemove(QString prefix, QString id);

private:
    DatabaseManager* m_databaseManager;

signals:

};

#endif // SIMPLEDATABASEMANAGER_H
