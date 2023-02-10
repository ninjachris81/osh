#include "shutteractor.h"

QLatin1String ShutterActor::CONFIG_TILT_SUPPORT = QLatin1String("tiltSupport");
QLatin1String ShutterActor::CONFIG_FULL_CLOSE_DURATION = QLatin1String("fullCloseDuration");
QLatin1String ShutterActor::CONFIG_FULL_TILT_DURATION = QLatin1String("fullTiltDuration");

int ShutterActor::CONFIG_FULL_CLOSE_DURATION_DEFAULT = 20000;
int ShutterActor::CONFIG_FULL_TILT_DURATION_DEFAULT = 2000;

ShutterActor::ShutterActor() : ActorBase() {
}

ShutterActor::ShutterActor(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent)
    : ActorBase(valueGroup, id, valueType, parent)
{

}

bool ShutterActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case actor::ACTOR_CMD_STOP:
    case actor::ACTOR_CMD_UP:
    case actor::ACTOR_CMD_DOWN:
    case actor::ACTOR_CMD_SHUTTER_HALF_CLOSE:
    case actor::ACTOR_CMD_SHUTTER_HALF_OPEN:
    case actor::ACTOR_CMD_SHUTTER_FULL_OPEN:
    case actor::ACTOR_CMD_SHUTTER_TURN_OPEN:
    case actor::ACTOR_CMD_SHUTTER_TURN_CLOSE:
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


void ShutterActor::_triggerCmd(actor::ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    switch(cmd) {
    case actor::ACTOR_CMD_STOP:
    case actor::ACTOR_CMD_UP:
    case actor::ACTOR_CMD_DOWN:
    case actor::ACTOR_CMD_SHUTTER_HALF_CLOSE:
    case actor::ACTOR_CMD_SHUTTER_HALF_OPEN:
    case actor::ACTOR_CMD_SHUTTER_FULL_OPEN:
    case actor::ACTOR_CMD_SHUTTER_TURN_OPEN:
    case actor::ACTOR_CMD_SHUTTER_TURN_CLOSE:
        break;
    default:
        iWarning() << "Cmd not supported" << cmd;
        break;
    }
}

void ShutterActor::updateClosePattern(unsigned char closeState) {
    int state = rawValue().toInt();
    state = setCloseState(state, closeState);
    ActorBase::updateValue(state);
}

void ShutterActor::updateTiltPattern(unsigned char tiltState) {
    if (!getConfig(CONFIG_TILT_SUPPORT, false).toBool()) {
        iWarning() << "Tilt not supported";
        return;
    }

    int state = rawValue().toInt();
    state = setTiltState(state, tiltState);
    ActorBase::updateValue(state);
}

int ShutterActor::setCloseState(int state, unsigned char closeState) {
    unsigned char tiltState = getTiltState(state);
    return setState(closeState, tiltState);
}

int ShutterActor::setTiltState(int state, unsigned char tiltState) {
    unsigned char closeState = getCloseState(state);
    return setState(closeState, tiltState);
}

int ShutterActor::setState(unsigned char closeState, unsigned char tiltState) {
    return (tiltState<<8) | (closeState);
}

unsigned char ShutterActor::getCloseState(int state) {
    return state & 0x00FF;
}

unsigned char ShutterActor::getTiltState(int state) {
    int v = state & 0xFF00;
    return v >> 8;
}

unsigned char ShutterActor::getCloseState() {
    return getCloseState(rawValue().toInt());
}

unsigned char ShutterActor::getTiltState() {
    return getTiltState(rawValue().toInt());
}
