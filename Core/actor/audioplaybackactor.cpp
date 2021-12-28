#include "audioplaybackactor.h"

AudioPlaybackActor::AudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QObject *parent) : ActorBase(valueGroup, id, valueType, parent)
{

}

bool AudioPlaybackActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case ACTOR_CMD_START:
    case ACTOR_CMD_PAUSE:
    case ACTOR_CMD_STOP:
        return true;
    default:
        return false;
    }
}

void AudioPlaybackActor::_triggerCmd(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case ACTOR_CMD_START:
        updateValue(true);
        break;
    case ACTOR_CMD_PAUSE:
        updateValue(false);
        break;
    case ACTOR_CMD_STOP:
        updateValue(false);
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
