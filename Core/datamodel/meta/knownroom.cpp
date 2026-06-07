#include "knownroom.h"
#include <QJsonArray>

QLatin1String KnownRoom::PROPERTY_NAME = QLatin1String("name");
QLatin1String KnownRoom::PROPERTY_KNOWN_AREA = QLatin1String("known_area_id");

KnownRoom::KnownRoom() : Identifyable() {
}

KnownRoom::KnownRoom(QString id, QObject *parent) : QObject(parent), Identifyable(id)
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
