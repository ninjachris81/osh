#include "actorbase.h"

#include <QDebug>

QLatin1String ActorBase::PROPERTY_IS_ASYNC = QLatin1String("is_async");
QLatin1String ActorBase::PROPERTY_PRIORITY = QLatin1String("priority");

ActorBase::ActorBase() : ValueBase() {
}

ActorBase::ActorBase(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QVariant::Type typeHint, QObject *parent) : ValueBase(valueGroup, id, valueType, true, typeHint, parent)
{

}

void ActorBase::triggerCmd(actor::ACTOR_CMDS cmd, QString reason) {
    iDebug() << Q_FUNC_INFO << cmd << reason;

    if (cmdSupported(cmd)) {
        _triggerCmd(cmd);
        Q_EMIT(cmdTriggered(cmd));
    } else {
        iWarning() << "Cmd not supported" << cmd;
    }
}

/*
void ActorBase::triggerCmd(int cmd) {
    iDebug() << Q_FUNC_INFO << cmd;
    triggerCmd(static_cast<ACTOR_CMDS>(cmd));
}
*/

void ActorBase::_triggerCmd(actor::ACTOR_CMDS cmd) {

}

ActorBase* ActorBase::withPriority(int priority) {
    this->m_priority = priority;
    return this;
}

int ActorBase::priority() {
    return m_priority;
}
