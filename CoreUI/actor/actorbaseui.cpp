#include "actorbaseui.h"

#include "actor/actorbase.h"

ActorBaseUI::ActorBaseUI(QObject *parent) : ValueBaseUI(parent)
{
    m_value = static_cast<ActorBase*>(parent);

}


void ActorBaseUI::triggerCmd(actor::ACTOR_CMDS cmd, QString reason) {
    static_cast<ActorBase*>(m_value)->triggerCmd(cmd, reason);
}
