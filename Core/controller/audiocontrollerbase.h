#ifndef AUDIOCONTROLLERBASE_H
#define AUDIOCONTROLLERBASE_H

#include <QObject>
#include <QList>
#include "controller/controllerbase.h"
#include "actor/audioplaybackactor.h"

class AudioControllerBase : public ControllerBase
{
    Q_OBJECT
public:
    explicit AudioControllerBase(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    virtual quint8 channelCount() = 0;

    /*virtual*/ quint8 bindActor(AudioPlaybackActor *actor);

    virtual void startPlayback(quint8 index) = 0;
    virtual void pausePlayback(quint8 index) = 0;
    virtual void stopPlayback(quint8 index) = 0;

signals:

protected:
    QString m_activateAmplGroupId = "";
    QString m_activateAmplActorId = "";
    quint8 m_actorCount = 0;
    QList<AudioPlaybackActor*> m_actorMappings;

};

#endif // AUDIOCONTROLLERBASE_H
