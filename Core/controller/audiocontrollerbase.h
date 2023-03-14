#ifndef AUDIOCONTROLLERBASE_H
#define AUDIOCONTROLLERBASE_H

#include <QObject>
#include <QList>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "actor/audioplaybackactor.h"

class SHARED_LIB_EXPORT AudioControllerBase : public ControllerBase
{
    Q_OBJECT
public:
    explicit AudioControllerBase(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    virtual void startPlayback(AudioPlaybackActor *audioActor) = 0;
    virtual void pausePlayback(AudioPlaybackActor *audioActor) = 0;
    virtual void stopPlayback(AudioPlaybackActor *audioActor) = 0;

signals:

protected:

};

#endif // AUDIOCONTROLLERBASE_H
