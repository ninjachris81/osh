#ifndef DOORACTOR_H
#define DOORACTOR_H

#include <QObject>

#include "sharedlib.h"

#include "actor/actorbase.h"

class SHARED_LIB_EXPORT DoorActor : public ActorBase
{
    Q_OBJECT
public:
    explicit DoorActor();
    explicit DoorActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, bool isAsync, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(actor::ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

protected:
    /*virtual*/ void _triggerCmd(actor::ACTOR_CMDS cmd);

signals:

};

#endif // DOORACTOR_H
