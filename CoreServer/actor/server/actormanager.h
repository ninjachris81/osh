#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#ifndef IS_OSH_CORE_SERVICE
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

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    void registerActor(ActorBase* actor);

signals:

public slots:
};

#endif // ACTORMANAGER_H
