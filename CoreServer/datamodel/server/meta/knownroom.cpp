#include "knownroom.h"

KnownRoom::KnownRoom(QString id, QObject *parent) : Identifyable(id, parent)
{

}


void KnownRoom::setName(QString name) {
    if (name == m_name) return;
    m_name = name;
    Q_EMIT(nameChanged());
}

QString KnownRoom::name() {
    return m_name;
}

void KnownRoom::addActor(ActorBase* actor) {
    m_actors.insert(actor->fullId(), actor);
}

void KnownRoom::addValue(ValueBase* value) {
    m_values.insert(value->fullId(), value);
}

QMap<QString, ActorBase*> KnownRoom::actors() {
    return m_actors;
}

QMap<QString, ValueBase*> KnownRoom::values() {
    return m_values;
}
