#ifndef CLIENTACTORMANAGER_H
#define CLIENTACTORMANAGER_H

#include <QObject>

#include <QMap>

#include "shared/actor_qt.h"
#include "manager/managerbase.h"
#include "actor/actorbase.h"

class ClientActorManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ClientActorManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    void registerActor(ActorBase* actor);

private:
    QMap<QString, ActorBase*> m_actors;


signals:

public slots:
};

#endif // CLIENTACTORMANAGER_H
