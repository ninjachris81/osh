#ifndef ACTORMESSAGE_H
#define ACTORMESSAGE_H

#include <QObject>

#include "sharedlib.h"

#include "communication/messagebase.h"
#include "value/valuemessage.h"
#include "shared/actor_qt.h"

using namespace actor;

class SHARED_LIB_EXPORT ActorMessage : public ValueMessage
{
    Q_OBJECT
public:
    explicit ActorMessage(QString actorGroupId, QString actorId, QVariant rawValue, ACTOR_CMDS cmd, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType() override;

    ACTOR_CMDS cmd();

protected:
    ACTOR_CMDS m_cmd;

signals:

public slots:
};

#endif // ACTORMESSAGE_H
