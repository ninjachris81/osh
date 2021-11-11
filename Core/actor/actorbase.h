#ifndef ACTORBASE_H
#define ACTORBASE_H

#include <QObject>

#include "value/valuebase.h"
#include "value/valuegroup.h"
#include "shared/actor_qt.h"

class ActorBase : public ValueBase
{
    Q_OBJECT
public:
    explicit ActorBase(ValueGroup* valueGroup, QString id, QObject *parent = nullptr);

    void triggerCmd(ACTOR_CMDS cmd);
    virtual bool cmdSupported(ACTOR_CMDS cmd) = 0;

    virtual bool isAsync() = 0;
signals:

protected:
    virtual void _triggerCmd(ACTOR_CMDS cmd) = 0;

public slots:
};

#endif // ACTORBASE_H
