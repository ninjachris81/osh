#include "timeractor.h"

#include <QDateTime>

TimerActor::TimerActor()
    : ActorBase{}
{}

TimerActor::TimerActor(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent) : ActorBase(valueGroup, id, valueType,QVariant::Int, parent) {

}

bool TimerActor::cmdSupported(ACTOR_CMDS cmd) {
    switch(cmd) {
    case ACTOR_CMDS::ACTOR_CMD_START:
    case ACTOR_CMDS::ACTOR_CMD_STOP:
        return true;
    default:
        return false;
    }
}

QVariant TimerActor::_updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::Int)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

bool TimerActor::isAsync() {
    return true;
}

void TimerActor::_triggerCmd(ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    switch(cmd) {
    case ACTOR_CMDS::ACTOR_CMD_START:
        updateValue(QDateTime::currentMSecsSinceEpoch(), true);
        break;
    case ACTOR_CMDS::ACTOR_CMD_STOP:
        invalidate();
        break;
    default:
        iWarning() << "Cmd not supported" << cmd;
        break;
    }
}
