#ifndef AUDIOPLAYBACKACTOR_H
#define AUDIOPLAYBACKACTOR_H

#include <QObject>

#include "sharedlib.h"

#include "actorbase.h"

class SHARED_LIB_EXPORT AudioPlaybackActor : public ActorBase
{
    Q_OBJECT
public:
    AudioPlaybackActor();
    explicit AudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

protected:
    /*virtual*/ void _triggerCmd(ACTOR_CMDS cmd);

signals:
    void startPlaybackRequested();
    void stopPlaybackRequested();
    void pausePlaybackRequested();

public slots:
};

#endif // AUDIOPLAYBACKACTOR_H
