#include "scripttriggeractor.h"

ScriptTriggerActor::ScriptTriggerActor(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent)
    : ActorBase(valueGroup, id, valueType, QVariant::String)
{
    Q_UNUSED(parent)
}

bool ScriptTriggerActor::cmdSupported(ACTOR_CMDS cmd) {
    return cmd == ACTOR_CMDS::ACTOR_CMD_TRIGGER_SCRIPT;
}

void ScriptTriggerActor::_triggerCmd(ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    switch(cmd) {
    case ACTOR_CMDS::ACTOR_CMD_TRIGGER_SCRIPT:
        Q_EMIT(triggerScript());
        break;
    default:
        iWarning() << "Cmd not supported" << cmd;
        break;
    }
}

QVariant ScriptTriggerActor::_updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    if (newValue.canConvert(QVariant::String)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}

bool ScriptTriggerActor::isAsync() {
    return false;
}
