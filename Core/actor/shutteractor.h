#ifndef SHUTTERACTOR_H
#define SHUTTERACTOR_H

#include <QObject>
#include "actorbase.h"
#include "shared/actor_qt.h"
#include "value/integervalue.h"

class ShutterActor : public ActorBase
{
    Q_OBJECT
public:
    explicit ShutterActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

    void setCloseState(IntegerValue* closeState);
    void setTiltState(IntegerValue* tiltState);

protected:
    /*virtual*/ void _triggerCmd(ACTOR_CMDS cmd);

    IntegerValue* m_closeState = nullptr;
    IntegerValue* m_tiltState = nullptr;

signals:

};

#endif // SHUTTERACTOR_H
