#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "user/oshuser.h"

class SHARED_LIB_EXPORT UserManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit UserManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    OshUser* user(QString id);

    void registerUser(OshUser* user);

private:
    QMap<QString, OshUser*> m_users;

signals:

};

#endif // USERMANAGER_H
