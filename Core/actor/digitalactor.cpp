#include "digitalactor.h"

#include <QDebug>

DigitalActor::DigitalActor() : ActorBase() {
}

DigitalActor::DigitalActor(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool isAsync, QObject *parent) : ActorBase(valueGroup, id, valueType, QVariant::Bool, parent), m_isAsync(isAsync)
{

}


bool DigitalActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case actor::ACTOR_CMD_ON:
    case actor::ACTOR_CMD_OFF:
        return true;
    default:
        return false;
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

void DigitalActor::_triggerCmd(actor::ACTOR_CMDS cmd) {
    Q_EMIT(statusRequested(cmd == actor::ACTOR_CMD_ON));

    if (!m_isAsync) {
        updateValue(cmd == actor::ACTOR_CMD_ON);
    }
}
