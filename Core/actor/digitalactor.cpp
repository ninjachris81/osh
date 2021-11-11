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
    qDebug() << Q_FUNC_INFO << cmd;

    switch(cmd) {
    case ACTOR_CMD_ON:
        updateValue(true);
        break;
    case ACTOR_CMD_OFF:
        updateValue(false);
        break;
    }

    Q_EMIT(valueChanged(rawValue().toBool()));
}

QVariant DigitalActor::_updateValue(QVariant newValue) {
    qDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::Bool)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

bool DigitalActor::isAsync() {
    return m_isAsync;
}
