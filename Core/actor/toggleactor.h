#ifndef TOGGLEACTOR_H
#define TOGGLEACTOR_H

#include <QObject>

#include "sharedlib.h"

#include "actorbase.h"
#include "shared/actor_qt.h"

#include "value/booleanvalue.h"

class SHARED_LIB_EXPORT ToggleActor : public ActorBase
{
    Q_OBJECT
public:
    explicit ToggleActor(ValueGroup* valueGroup, QString id, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(actor::ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

protected:
    /*virtual*/ void _triggerCmd(actor::ACTOR_CMDS cmd);


signals:
    //void requestToggle();

};

#endif // TOGGLEACTOR_H
