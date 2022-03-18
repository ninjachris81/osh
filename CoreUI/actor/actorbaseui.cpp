#include "actorbaseui.h"

#include "actor/actorbase.h"

ActorBaseUI::ActorBaseUI(QObject *parent) : ValueBaseUI(parent)
{
    m_actor = static_cast<ActorBase*>(parent);
}

ActorBase* ActorBaseUI::parent() {
    return m_actor;
}

void ActorBaseUI::triggerCmd(actor::ACTOR_CMDS cmd, QString reason) {
    static_cast<ActorBase*>(m_value)->triggerCmd(cmd, reason);
}
