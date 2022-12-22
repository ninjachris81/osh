#include "user.h"

QLatin1String User::USER_RIGHT_UNLOCK_DOOR = QLatin1String("unlock_door");

User::User(QString id, QObject *parent) : QObject(parent), SerializableIdentifyable(id)
{

}

void User::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);
    obj.insert("rights", m_rights.join(","));
}

void User::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);
    m_rights = obj.value("rights").toString().split(",");
}

QString User::getClassName() {
    return staticMetaObject.className();
}

LogCat::LOGCAT User::logCat() {
    return LogCat::USER;
}

QStringList User::rights() {
    return m_rights;
}
