#include "toggleactor.h"

#include <QDebug>


ToggleActor::ToggleActor(ValueGroup *valueGroup, QString id, QObject *parent)
    : ActorBase(valueGroup, id, VALUE_TYPE::VALTYPE_VIRTUAL_ACTOR, parent)
{
    m_alwaysEmit = false;
}

bool ToggleActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    return cmd == actor::ACTOR_CMD_TOGGLE;
}

QVariant ToggleActor::_updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::Bool)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

bool ToggleActor::isAsync() {
    return false;
}

void ToggleActor::_triggerCmd(actor::ACTOR_CMDS cmd) {
    if (cmd == actor::ACTOR_CMD_TOGGLE) {
        Q_EMIT(requestToggle());
    }
}
