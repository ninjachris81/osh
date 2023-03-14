#ifndef AUDIOCONTROLLERSIMULATOR_H
#define AUDIOCONTROLLERSIMULATOR_H

#include <QObject>
#include <QList>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "actor/audioplaybackactor.h"
#include "controller/audiocontrollerbase.h"

class SHARED_LIB_EXPORT AudioControllerSimulator : public AudioControllerBase
{
    Q_OBJECT
public:
    explicit AudioControllerSimulator(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void startPlayback(AudioPlaybackActor* audioActor) override;
    /*virtual*/ void pausePlayback(AudioPlaybackActor* audioActor) override;
    /*virtual*/ void stopPlayback(AudioPlaybackActor* audioActor) override;

signals:

protected:
    QString m_activateAmplGroupId = "";
    QString m_activateAmplActorId = "";
    quint8 m_actorCount = 0;
    QList<AudioPlaybackActor*> m_actorMappings;

};

#endif // AUDIOCONTROLLERSIMULATOR_H
