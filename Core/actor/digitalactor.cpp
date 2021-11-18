#include "digitalactor.h"

#include <QDebug>

DigitalActor::DigitalActor(ValueGroup *valueGroup, QString id, bool isAsync, QObject *parent) : ActorBase(valueGroup, id, parent), m_isAsync(isAsync)
{

}


bool DigitalActor::cmdSupported(ACTOR_CMDS cmd) {
    switch(cmd) {
    case ACTOR_CMD_ON:
    case ACTOR_CMD_OFF:
        return true;
    default:
        return false;
    }
}

void DigitalActor::_triggerCmd(ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    switch(cmd) {
    case ACTOR_CMD_ON:
        Q_EMIT(statusRequested(true));
        break;
    case ACTOR_CMD_OFF:
        Q_EMIT(statusRequested(false));
        break;
    default:
        iWarning() << "Cmd not supported" << cmd;
        break;
    }
}

QVariant DigitalActor::_updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::Bool)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

bool DigitalActor::isAsync() {
    return m_isAsync;
}
