#include "audioplaybackactor.h"

QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_DEVICE_ID = QLatin1String("audioDeviceId");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_ACTIVATION_RELAY_ID = QLatin1String("audioActivationRelayId");

AudioPlaybackActor::AudioPlaybackActor() : ActorBase() {
}

AudioPlaybackActor::AudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QString audioDeviceId, QString audioActivationRelayId, QObject *parent) : ActorBase(valueGroup, id, valueType, parent), m_audioDeviceId(audioDeviceId), m_audioActivationRelayId(audioActivationRelayId)
{

}

bool AudioPlaybackActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case actor::ACTOR_CMD_START:
    case actor::ACTOR_CMD_PAUSE:
    case actor::ACTOR_CMD_STOP:
        return true;
    default:
        return false;
    }
}

void AudioPlaybackActor::_triggerCmd(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case actor::ACTOR_CMD_START:
        Q_EMIT(startPlaybackRequested());
        break;
    case actor::ACTOR_CMD_PAUSE:
        Q_EMIT(pausePlaybackRequested());
        break;
    case actor::ACTOR_CMD_STOP:
        Q_EMIT(stopPlaybackRequested());
        break;
    }
}

QVariant AudioPlaybackActor::_updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::String)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

bool AudioPlaybackActor::isAsync() {
    return true;
}

QString AudioPlaybackActor::audioDeviceId() {
    return m_audioDeviceId;
}

QString AudioPlaybackActor::audioActivationRelayId() {
    return m_audioActivationRelayId;
}

int AudioPlaybackActor::priority() {
    return m_priority;
}
