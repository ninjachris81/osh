#ifndef AUDIOPLAYBACKACTOR_H
#define AUDIOPLAYBACKACTOR_H

#include <QObject>

#include "sharedlib.h"

#include "actorbase.h"

class SHARED_LIB_EXPORT AudioPlaybackActor : public ActorBase
{
    Q_OBJECT
public:
    static QLatin1String PROPERTY_AUDIO_DEVICE_ID;
    static QLatin1String PROPERTY_AUDIO_ACTIVATION_RELAY_ID;
    static QLatin1String PROPERTY_AUDIO_VOLUME;

    AudioPlaybackActor();
    explicit AudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QString audioDeviceId, QString audioActivationRelayId, float audioVolume, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(actor::ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

    QString audioDeviceId();
    QString audioActivationRelayId();
    float audioVolume();

protected:
    QString m_audioDeviceId = "";
    QString m_audioActivationRelayId = "";
    float m_audioVolume = 1;

    /*virtual*/ void _triggerCmd(actor::ACTOR_CMDS cmd);

signals:
    void startPlaybackRequested();
    void stopPlaybackRequested();
    void pausePlaybackRequested();

public slots:
};

#endif // AUDIOPLAYBACKACTOR_H
