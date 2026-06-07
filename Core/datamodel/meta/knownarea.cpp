#include "knownarea.h"
#include <QJsonArray>

QLatin1String KnownArea::PROPERTY_NAME = QLatin1String("name");

KnownArea::KnownArea() : Identifyable() {
}

KnownArea::KnownArea(QString id, QObject *parent) : QObject(parent), Identifyable(id)
{
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
