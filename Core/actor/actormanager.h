#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#include <QObject>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "actor/actorbase.h"
#include "communication/communicationmanagerbase.h"

class SHARED_LIB_EXPORT ActorManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ActorManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void registerActor(ActorBase* actor, ValueManagerBase* valueManager);

    void publishCmd(ActorBase *actor, actor::ACTOR_CMDS cmd);

    //void onCmdTriggered(ActorBase *actor, actor::ACTOR_CMDS cmd);

private:
    QMap<QString, ActorBase*> m_actors;
    CommunicationManagerBase* m_commManager;

private slots:

signals:

public slots:
};

#endif // ACTORMANAGER_H
