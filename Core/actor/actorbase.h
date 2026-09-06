#pragma once

#include <QObject>

#include "sharedlib.h"

#include "value/valuebase.h"
#include "value/valuegroup.h"
#include "shared/actor_qt.h"

using namespace actor;

class SHARED_LIB_EXPORT ActorBase : public ValueBase
{
    Q_OBJECT

public:
    static QLatin1String PROPERTY_IS_ASYNC;
    static QLatin1String PROPERTY_PRIORITY;

    explicit ActorBase();
    ActorBase(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QVariant::Type typeHint, QObject *parent = nullptr);

    void triggerCmd(ACTOR_CMDS cmd, QString reason);
    virtual bool cmdSupported(ACTOR_CMDS cmd) = 0;

    ActorBase* withPriority(int priority);
    int priority();

    /*
     * If async, this means that the value will not be immediately set
     * instead, the command might be triggered first and later the value will change
     */
    virtual bool isAsync() = 0;

protected:
    int m_priority = 0;

Q_SIGNALS:
    void cmdTriggered(ACTOR_CMDS cmd);

protected:
    virtual void _triggerCmd(ACTOR_CMDS cmd);

public slots:
};

