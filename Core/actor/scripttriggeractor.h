#ifndef SCRIPTTRIGGERACTOR_H
#define SCRIPTTRIGGERACTOR_H

#include <QObject>

#include "sharedlib.h"

#include "actor/actorbase.h"

class SHARED_LIB_EXPORT ScriptTriggerActor : public ActorBase
{
    Q_OBJECT
public:
    explicit ScriptTriggerActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(actor::ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

protected:
    /*virtual*/ void _triggerCmd(actor::ACTOR_CMDS cmd);

signals:
    void triggerScript();

};

#endif // SCRIPTTRIGGERACTOR_H
