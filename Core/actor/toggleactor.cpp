#include "toggleactor.h"

#include <QDebug>


ToggleActor::ToggleActor(ValueGroup *valueGroup, QString id, QObject *parent)
    : ActorBase(valueGroup, id, VALUE_TYPE::VALTYPE_VIRTUAL_ACTOR, QVariant::Bool, parent)
{
    m_alwaysEmit = false;
}

bool ToggleActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case actor::ACTOR_CMD_ON:
    case actor::ACTOR_CMD_OFF:
    case actor::ACTOR_CMD_TOGGLE:
        return true;
    default:
        return false;
    }
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
    switch(cmd) {
    case actor::ACTOR_CMD_ON:
        updateValue(true);
        break;
    case actor::ACTOR_CMD_OFF:
        updateValue(false);
        break;
    case actor::ACTOR_CMD_TOGGLE:
        updateValue(!rawValue().toBool());
        break;
    default:
        break;
    }
}
