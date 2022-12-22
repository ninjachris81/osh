#ifndef CAMERAACTOR_H
#define CAMERAACTOR_H

#include <QObject>

#include "sharedlib.h"

#include "actorbase.h"
#include "shared/actor_qt.h"

class SHARED_LIB_EXPORT CameraActor : public ActorBase
{
    Q_OBJECT
public:
    explicit CameraActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(actor::ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

protected:
    /*virtual*/ void _triggerCmd(actor::ACTOR_CMDS cmd);

signals:

};

#endif // CAMERAACTOR_H
