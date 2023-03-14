#include "audioplaybackactor.h"

#include "helpers.h"

QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_DEVICE_IDS = QLatin1String("audioDeviceIds");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_ACTIVATION_RELAY_ID = QLatin1String("audioActivationRelayId");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_VOLUME = QLatin1String("audioVolume");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_VOLUME_ID = QLatin1String("audioVolumeId");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_DEFAULT_URL = QLatin1String("audioDefaultUrl");

AudioPlaybackActor::AudioPlaybackActor() : ActorBase() {
}

AudioPlaybackActor::AudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QString audioDeviceIds, QString audioActivationRelayId, float audioVolume, QString audioVolumeId, QString audioDefaultUrl, QObject *parent) : ActorBase(valueGroup, id, valueType, parent),
    m_audioActivationRelayId(audioActivationRelayId), m_audioVolume(audioVolume), m_audioVolumeId(audioVolumeId), m_audioDefaultUrl(audioDefaultUrl)
{
    m_audioDeviceIds = audioDeviceIds.split("\n");
    updateValue(m_audioDefaultUrl, false);
}

bool AudioPlaybackActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case actor::ACTOR_CMD_SET_VALUE:
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

QStringList AudioPlaybackActor::audioDeviceIds() {
    return m_audioDeviceIds;
}

QString AudioPlaybackActor::audioActivationRelayId() {
    return m_audioActivationRelayId;
}

float AudioPlaybackActor::audioVolume() {
    return m_audioVolume;
}

QString AudioPlaybackActor::audioVolumeId() {
    return m_audioVolumeId;
}

QString AudioPlaybackActor::audioDefaultUrl() {
    return m_audioDefaultUrl;
}

AudioPlaybackActor* AudioPlaybackActor::withAudioVolumeValue(DoubleValue* volume) {
    iDebug() << Q_FUNC_INFO << volume->fullId();

    if (volume->valueType() != value::VALTYPE_AUDIO_VOLUME) {
        iWarning() << "Value" << volume->fullId() << "has wrong value type";
    }

    m_audioVolumeValue = volume;

    Helpers::safeConnect(m_audioVolumeValue, &DoubleValue::valueChanged, this, &AudioPlaybackActor::onVolumeChanged, SIGNAL(valueChanged()), SLOT(onVolumeChanged()));
    return this;
}

void AudioPlaybackActor::onVolumeChanged() {
    m_audioVolume = m_audioVolumeValue->rawValue().toFloat();
    Q_EMIT(volumeChanged());
}

