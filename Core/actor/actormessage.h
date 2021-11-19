#ifndef ACTORMESSAGE_H
#define ACTORMESSAGE_H

#include <QObject>
#include "communication/messagebase.h"
#include "shared/actor_qt.h"

using namespace actor;

class ActorMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit ActorMessage(QString actorGroupId, QString actorId, ACTOR_CMDS cmd, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();

    QString actorGroupId();
    QString actorId();
    QString fullId();
    ACTOR_CMDS cmd();

protected:
    QString m_actorGroupId;
    QString m_actorId;
    ACTOR_CMDS m_cmd;

signals:

public slots:
};

#endif // ACTORMESSAGE_H
