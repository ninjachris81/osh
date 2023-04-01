#include "oshuser.h"

QLatin1String OshUser::USER_RIGHT_UNLOCK_DOOR = QLatin1String("unlock_door");

QLatin1String OshUser::PROPERTY_NAME = QLatin1String("name");
QLatin1String OshUser::PROPERTY_RIGHTS = QLatin1String("rights");

OshUser::OshUser(QString id, QString name, QStringList rights, QObject *parent) : QObject(parent), SerializableIdentifyable(id),
  m_name(name), m_rights(rights)
{
}

void OshUser::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);
    obj.insert("rights", m_rights.join(","));
}

void OshUser::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);
    m_rights = obj.value("rights").toString().split(",");
}

QString OshUser::getClassName() {
    return staticMetaObject.className();
}

LogCat::LOGCAT OshUser::logCat() {
    return LogCat::USER;
}

QString OshUser::name() {
    return m_name;
}

QStringList OshUser::rights() {
    return m_rights;
}
