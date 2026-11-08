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
        startTimer();
        break;
    case ACTOR_CMDS::ACTOR_CMD_STOP:
        stopTimer();
        break;
    default:
        iWarning() << "Cmd not supported" << cmd;
        break;
    }
}

void TimerActor::startTimer() {
    if (valueTimeout() == ValueBase::VT_NONE) {
        iWarning() << "TimerActor" << fullId() << "has no timeout set, cannot start";
        return;
    }

    m_startTime = QDateTime::currentMSecsSinceEpoch();
    m_isRunning = true;
    updateValue(calculateMsLeft(), true);
}

void TimerActor::updateTimeLeft() {
    if (!m_isRunning) {
        return;
    }

    quint64 secondsLeft = calculateMsLeft();
    if (secondsLeft <= 0) {
        stopTimer();
    } else {
        updateValue(secondsLeft, true);
    }
}

quint64 TimerActor::calculateMsLeft() {
    if (!m_isRunning) {
        return 0;
    }

    quint64 elapsed = QDateTime::currentMSecsSinceEpoch() - m_startTime;
    quint64 timeout = valueTimeout();
    if (elapsed >= timeout) {
        return 0;
    } else {
        return (timeout - elapsed);
    }
}

void TimerActor::stopTimer() {
    m_isRunning = false;
    m_startTime = 0;
    emit cmdTriggered(ACTOR_CMDS::ACTOR_CMD_STOP);
    // invalidation happens in ServerValueManager::checkValues() when the value is checked and the timer is not running anymore
}

bool TimerActor::isRunning() {
    return m_isRunning;
}