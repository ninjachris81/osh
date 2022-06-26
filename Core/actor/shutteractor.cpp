#include "shutteractor.h"

ShutterActor::ShutterActor(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent)
    : ActorBase(valueGroup, id, valueType, parent)
{

}

bool ShutterActor::cmdSupported(ACTOR_CMDS cmd) {
    switch(cmd) {
    case ACTOR_CMD_UP:
    case ACTOR_CMD_DOWN:
        return true;
    default:
        return false;
    }
}

QVariant ShutterActor::_updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::Int)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

bool ShutterActor::isAsync() {
    return true;
}


void ShutterActor::_triggerCmd(ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    switch(cmd) {
    case ACTOR_CMD_UP:
        break;
    case ACTOR_CMD_DOWN:
        break;
    default:
        iWarning() << "Cmd not supported" << cmd;
        break;
    }
}


void ShutterActor::setCloseState(IntegerValue* closeState) {
    m_closeState = closeState;
}

void ShutterActor::setTiltState(IntegerValue* tiltState) {
    m_tiltState = tiltState;
}
