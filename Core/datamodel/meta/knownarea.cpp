#include "knownarea.h"
#include <QJsonArray>

QLatin1String KnownArea::PROPERTY_NAME = QLatin1String("name");

KnownArea::KnownArea() : SerializableIdentifyable() {
}

KnownArea::KnownArea(QString id, QObject *parent) : QObject(parent), SerializableIdentifyable(id)
{

}
void KnownArea::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);

    obj.insert("name", m_name);

    QJsonArray knownRooms;
    for (QString valueId : m_knownRooms.keys()) {
        knownRooms.append(valueId);
    }
    obj.insert("knownRooms", knownRooms);
}

void KnownArea::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);

    m_name = obj.value("name").toString();
}

QString KnownArea::getClassName() {
    return staticMetaObject.className();
}

void KnownArea::setName(QString name) {
    if (name == m_name) return;
    m_name = name;
    Q_EMIT(nameChanged());
}

QString KnownArea::name() {
    return m_name;
}

void KnownArea::addKnownRoom(KnownRoom* knownRoom) {
    m_knownRooms.insert(knownRoom->id(), knownRoom);
}

QMap<QString, KnownRoom*> KnownArea::knownRooms() {
    return m_knownRooms;
}
