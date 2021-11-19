#include "actorbaseui.h"

#include "actor/actorbase.h"

ActorBaseUI::ActorBaseUI(QObject *parent) : ValueBaseUI(parent)
{
    m_value = static_cast<ActorBase*>(parent);

}
