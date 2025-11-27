#include "cameraactor.h"

CameraActor::CameraActor(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent) : ActorBase(valueGroup, id, valueType, QVariant::Bool, parent)
{
}


bool CameraActor::cmdSupported(ACTOR_CMDS cmd) {
    switch(cmd) {
    case ACTOR_CMDS::ACTOR_CMD_ON:
    case ACTOR_CMDS::ACTOR_CMD_OFF:
        return true;
    default:
        return false;
    }
}

void CameraActor::_triggerCmd(ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    switch(cmd) {
    case ACTOR_CMDS::ACTOR_CMD_ON:
        //Q_EMIT(statusRequested(true));
        break;
    case ACTOR_CMDS::ACTOR_CMD_OFF:
        //Q_EMIT(statusRequested(false));
        break;
    default:
        iWarning() << "Cmd not supported" << cmd;
        break;
    }
}

QVariant CameraActor::_updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::Bool)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

bool CameraActor::isAsync() {
    return true;
}
