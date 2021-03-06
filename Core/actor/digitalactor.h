#ifndef DIGITALACTOR_H
#define DIGITALACTOR_H

#include <QObject>
#include "actorbase.h"
#include "shared/actor_qt.h"

#include "value/booleanvalue.h"

class DigitalActor : public ActorBase
{
    Q_OBJECT
public:
    explicit DigitalActor();
    explicit DigitalActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, bool isAsync, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

protected:
    bool m_isAsync;

    /*virtual*/ void _triggerCmd(ACTOR_CMDS cmd);

signals:
    void statusRequested(bool status);

public slots:
};

#endif // DIGITALACTOR_H
