#include "knownroomui.h"
#include "value/valuebaseui.h"
#include "actor/actorbaseui.h"

KnownRoomUI::KnownRoomUI( QObject *parent) : VisualItemBase(parent)
{
    m_knownRoom = static_cast<KnownRoom*>(parent);

    connect(m_knownRoom, &KnownRoom::nameChanged, this, &KnownRoomUI::nameChanged);

    QMapIterator<QString, ValueBase*> it(m_knownRoom->values());
    while(it.hasNext()) {
        it.next();
        m_values.append(new ValueBaseUI(it.value()));
    }

    QMapIterator<QString, ActorBase*> it2(m_knownRoom->actors());
    while(it2.hasNext()) {
        it2.next();
        m_actors.append(new ActorBaseUI(it2.value()));
    }
}

QList<QObject*> KnownRoomUI::values() {
    return m_values;
}

QList<QObject*> KnownRoomUI::actors() {
    return m_actors;
}

QString KnownRoomUI::name() {
    return m_knownRoom->name();
}
