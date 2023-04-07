#include "dooractor.h"

#include <QDebug>

DoorActor::DoorActor() : ActorBase() {
}

DoorActor::DoorActor(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent) : ActorBase(valueGroup, id, valueType, QVariant::Bool, parent)
{

}


bool DoorActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case actor::ACTOR_CMD_ON:
    case actor::ACTOR_CMD_OFF:
        return true;
    default:
        return false;
    }
}

void DoorActor::_triggerCmd(actor::ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    switch(cmd) {
    case actor::ACTOR_CMD_ON:
        break;
    case actor::ACTOR_CMD_OFF:
        break;
    default:
        iWarning() << "Cmd not supported" << cmd;
        break;
    }
}

QVariant DoorActor::_updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::Bool)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

bool DoorActor::isAsync() {
    return false;
}
