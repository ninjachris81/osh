#ifndef ACTORBASE_H
#define ACTORBASE_H

#include <QObject>

#include "value/valuebase.h"
#include "value/valuegroup.h"
#include "shared/actor_qt.h"

using namespace actor;

class ActorBase : public ValueBase
{
    Q_OBJECT
public:
    explicit ActorBase(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    void triggerCmd(ACTOR_CMDS cmd, QString reason);
    //Q_INVOKABLE void triggerCmd(int cmd);
    virtual bool cmdSupported(ACTOR_CMDS cmd) = 0;

    virtual bool isAsync() = 0;

signals:
    void cmdTriggered(ACTOR_CMDS cmd);

protected:
    virtual void _triggerCmd(ACTOR_CMDS cmd) = 0;

public slots:
};

#endif // ACTORBASE_H
