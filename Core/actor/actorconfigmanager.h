#ifndef ACTORCONFIGMANAGER_H
#define ACTORCONFIGMANAGER_H

#include <QObject>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "actor/actorbase.h"
#include "actor/actormanager.h"
#include "communication/communicationmanagerbase.h"

class SHARED_LIB_EXPORT ActorConfigManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ActorConfigManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

private slots:
    void onBroadcastConfig();

signals:

private:
    ActorManager* m_actorManager;
    CommunicationManagerBase* m_commManager;

};

#endif // ACTORCONFIGMANAGER_H
