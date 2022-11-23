#ifndef CLIENTACTORMANAGER_H
#define CLIENTACTORMANAGER_H

#include <QObject>
#include <QMap>

#include "sharedlib.h"

#include "shared/actor_qt.h"
#include "manager/managerbase.h"
#include "actor/actorbase.h"

class SHARED_LIB_EXPORT ClientActorManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ClientActorManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString id();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    void registerActor(ActorBase* actor);

private:
    QMap<QString, ActorBase*> m_actors;


signals:

public slots:
};

#endif // CLIENTACTORMANAGER_H
