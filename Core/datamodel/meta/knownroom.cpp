#include "knownroom.h"
#include <QJsonArray>

QLatin1String KnownRoom::PROPERTY_NAME = QLatin1String("name");
QLatin1String KnownRoom::PROPERTY_KNOWN_AREA = QLatin1String("knownArea");

KnownRoom::KnownRoom() : SerializableIdentifyable() {
}

KnownRoom::KnownRoom(QString id, QObject *parent) : QObject(parent), SerializableIdentifyable(id)
{

}
void KnownRoom::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);

    obj.insert("name", m_name);

    QJsonArray values;
    for (QString valueId : m_values.keys()) {
        values.append(valueId);
    }
    obj.insert("values", values);

    QJsonArray actors;
    for (QString actorId : m_actors.keys()) {
        actors.append(actorId);
    }
    obj.insert("actors", actors);
}

void KnownRoom::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);

    m_name = obj.value("name").toString();
}

QString KnownRoom::getClassName() {
    return staticMetaObject.className();
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
