#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#if ! defined(IS_OSH_CORE_SERVICE) && ! defined(IS_OSH_UI)
    #error Should use client version
#endif

#include <QObject>

#include "manager/managerbase.h"
#include "actor/actorbase.h"
#include "communication/communicationmanagerbase.h"

class ActorManager : public ManagerBase
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

    void registerActor(ActorBase* actor);

    void onCmdTriggered(ActorBase *actor, ACTOR_CMDS cmd);

private:
    QMap<QString, ActorBase*> m_actors;
    CommunicationManagerBase* m_commManager;

private slots:

signals:

public slots:
};

#endif // ACTORMANAGER_H
