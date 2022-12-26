#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "user/user.h"
#include "database/databasemanager.h"

class SHARED_LIB_EXPORT UserManager : public ManagerBase
{
    Q_OBJECT
public:
    static QLatin1String USER_TABLE_NAME;

    explicit UserManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    User* getUser(QString id);



private:
    DatabaseManager* m_databaseManager;
signals:

};

#endif // USERMANAGER_H
