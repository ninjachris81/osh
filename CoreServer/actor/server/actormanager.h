#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#if ! defined(IS_OSH_CORE_SERVICE) && ! defined(IS_OSH_UI)
    #error Should use client version
#endif

#include <QObject>

#include "manager/managerbase.h"
#include "actor/actorbase.h"

class ActorManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ActorManager(QObject *parent = nullptr);

    static QLatin1Literal MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void registerActor(ActorBase* actor);

private:
    QMap<QString, ActorBase*> m_actors;

signals:

public slots:
};

#endif // ACTORMANAGER_H
