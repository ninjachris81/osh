#ifndef VALUEACTOR_H
#define VALUEACTOR_H

#include <QObject>

#include "sharedlib.h"

#include "actorbase.h"
#include "shared/actor_qt.h"

/*
 * receives SET_VALUE commands & executes set of value
*/
class SHARED_LIB_EXPORT ValueActor : public ActorBase
{
    Q_OBJECT
public:
    explicit ValueActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QVariant::Type typeHint, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(actor::ACTOR_CMDS cmd) override;

    /*virtual*/ bool isAsync() override;

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

protected:
    /*virtual*/ void _triggerCmd(actor::ACTOR_CMDS cmd) override;

signals:
    void requestSetValue();

};

#endif // VALUEACTOR_H
