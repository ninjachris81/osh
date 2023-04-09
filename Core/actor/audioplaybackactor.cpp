#include "audioplaybackactor.h"

#include "helpers.h"

QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_DEVICE_IDS = QLatin1String("audio_device_ids");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_ACTIVATION_RELAY_ID = QLatin1String("audio_activation_relay_id");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_VOLUME = QLatin1String("audio_volume");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_VOLUME_ID = QLatin1String("audio_volume_id");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_URL = QLatin1String("audio_url");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_URL_ID = QLatin1String("audio_url_id");
QLatin1String AudioPlaybackActor::PROPERTY_AUDIO_CURRENT_TITLE_ID = QLatin1String("audio_current_title_id");

AudioPlaybackActor::AudioPlaybackActor() : ActorBase() {
}

AudioPlaybackActor::AudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QString audioDeviceIds, QString audioActivationRelayId, float audioVolume, QString audioVolumeId, QString audioUrl, QString audioUrlId, QString audioCurrentTitleId, QObject *parent) : ActorBase(valueGroup, id, valueType, QVariant::Int, parent),
    m_audioActivationRelayId(audioActivationRelayId), m_audioVolume(audioVolume), m_audioVolumeId(audioVolumeId), m_audioUrl(audioUrl), m_audioUrlId(audioUrlId)
{
    m_audioDeviceIds = audioDeviceIds.split("\n");
}

bool AudioPlaybackActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case actor::ACTOR_CMD_START:
    case actor::ACTOR_CMD_PAUSE:
    case actor::ACTOR_CMD_STOP:
    case actor::ACTOR_CMD_NEXT:
    case actor::ACTOR_CMD_PREVIOUS:
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
    case actor::ACTOR_CMD_NEXT:
        Q_EMIT(nextRequested());
        break;
    case actor::ACTOR_CMD_PREVIOUS:
        Q_EMIT(previousRequested());
        break;
    }
}

QVariant AudioPlaybackActor::_updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::Int)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

AudioPlaybackActor::AudioPlaybackState AudioPlaybackActor::playbackState() {
    return static_cast<AudioPlaybackState>(rawValue().toInt());
}

void AudioPlaybackActor::setPlaybackState(AudioPlaybackState state) {
    updateValue(state, false);
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
    if (m_audioVolumeValue->rawValue().isValid()) m_audioVolume = m_audioVolumeValue->rawValue().toFloat();
    return m_audioVolume;
}

QString AudioPlaybackActor::audioVolumeId() {
    return m_audioVolumeId;
}

QString AudioPlaybackActor::audioUrl() {
    if (m_audioUrlValue->rawValue().isValid()) m_audioUrl = m_audioUrlValue->rawValue().toString();
    return m_audioUrl;
}

QString AudioPlaybackActor::audioUrlId() {
    return m_audioUrlId;
}

QString AudioPlaybackActor::audioCurrentTitleId() {
    if (m_audioCurrentTitleValue != nullptr && m_audioCurrentTitleValue->rawValue().isValid()) {
        return m_audioCurrentTitleValue->rawValue().toString();
    } else {
        return "";
    }
}

StringValue *AudioPlaybackActor::audioCurrentTitle() {
    return m_audioCurrentTitleValue;
}

AudioPlaybackActor* AudioPlaybackActor::withAudioVolumeValue(DoubleValue* volume) {
    iDebug() << Q_FUNC_INFO << volume->fullId();

    if (volume->valueType() != value::VALTYPE_AUDIO_VOLUME) {
        iWarning() << "Value" << volume->fullId() << "has wrong value type";
    }

    m_audioVolumeValue = volume;
    if (m_audioVolumeValue->rawValue().isValid()) m_audioVolume = m_audioVolumeValue->rawValue().toFloat();

    Helpers::safeConnect(m_audioVolumeValue, &DoubleValue::valueChanged, this, &AudioPlaybackActor::onVolumeChanged, SIGNAL(valueChanged()), SLOT(onVolumeChanged()));

    return this;
}

AudioPlaybackActor* AudioPlaybackActor::withAudioUrlValue(StringValue* url) {
    iDebug() << Q_FUNC_INFO << url->fullId();

    if (url->valueType() != value::VALTYPE_SOUND_URL) {
        iWarning() << "Value" << url->fullId() << "has wrong value type";
    }

    m_audioUrlValue = url;
    if (m_audioUrlValue->rawValue().isValid()) m_audioUrl = m_audioUrlValue->rawValue().toString();

    Helpers::safeConnect(m_audioUrlValue, &StringValue::valueChanged, this, &AudioPlaybackActor::onUrlChanged, SIGNAL(valueChanged()), SLOT(onUrlChanged()));
    return this;
}

AudioPlaybackActor* AudioPlaybackActor::withAudioCurrentTitleValue(StringValue *currentTitle) {
    iDebug() << Q_FUNC_INFO << currentTitle->fullId();
    m_audioCurrentTitleValue = currentTitle;
    return this;
}

void AudioPlaybackActor::onVolumeChanged() {
    m_audioVolume = m_audioVolumeValue->rawValue().toFloat();
    Q_EMIT(volumeChanged());
}

void AudioPlaybackActor::onUrlChanged() {
    m_audioUrl = m_audioUrlValue->rawValue().toString();
    Q_EMIT(urlChanged());
}
