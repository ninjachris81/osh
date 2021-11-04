#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#include <QObject>

#include "manager/managerbase.h"

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

signals:

public slots:
};

#endif // ACTORMANAGER_H
