#ifndef AUDIOPLAYBACKACTOR_H
#define AUDIOPLAYBACKACTOR_H

#include <QObject>

#include "actorbase.h"

class AudioPlaybackActor : public ActorBase
{
    Q_OBJECT
public:
    explicit AudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

protected:
    /*virtual*/ void _triggerCmd(ACTOR_CMDS cmd);
signals:

public slots:
};

#endif // AUDIOPLAYBACKACTOR_H
