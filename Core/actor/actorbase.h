#ifndef ACTORBASE_H
#define ACTORBASE_H

#include <QObject>

#include "sharedlib.h"

#include "value/valuebase.h"
#include "value/valuegroup.h"
#include "shared/actor_qt.h"

class SHARED_LIB_EXPORT ActorBase : public ValueBase
{
    Q_OBJECT
public:
    static QLatin1String PROPERTY_IS_ASYNC;

    explicit ActorBase();
    explicit ActorBase(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    void triggerCmd(actor::ACTOR_CMDS cmd, QString reason);
    virtual bool cmdSupported(actor::ACTOR_CMDS cmd) = 0;

    virtual bool isAsync() = 0;

Q_SIGNALS:
    void cmdTriggered(actor::ACTOR_CMDS cmd);

protected:
    virtual void _triggerCmd(actor::ACTOR_CMDS cmd);

public slots:
};

#endif // ACTORBASE_H
