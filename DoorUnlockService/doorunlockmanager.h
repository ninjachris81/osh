#ifndef DOORUNLOCKMANAGER_H
#define DOORUNLOCKMANAGER_H

#include <QObject>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"
#include "user/usermanager.h"

class DoorUnlockManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit DoorUnlockManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ QString id() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

private:
    CommunicationManagerBase* m_commManager;
    UserManager* m_userManager;

signals:

};

#endif // DOORUNLOCKMANAGER_H
