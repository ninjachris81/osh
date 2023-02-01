#include "audioplaybackactor.h"

AudioPlaybackActor::AudioPlaybackActor() : ActorBase() {
}

AudioPlaybackActor::AudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QObject *parent) : ActorBase(valueGroup, id, valueType, parent)
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
        updateValue(true);
        Q_EMIT(startPlaybackRequested());
        break;
    case actor::ACTOR_CMD_PAUSE:
        updateValue(false);
        Q_EMIT(pausePlaybackRequested());
        break;
    case actor::ACTOR_CMD_STOP:
        updateValue(false);
        Q_EMIT(stopPlaybackRequested());
        break;
    }
}

QVariant AudioPlaybackActor::_updateValue(QVariant newValue) {
    // TBD
    return QVariant();
}

bool AudioPlaybackActor::isAsync() {
    return true;
}
