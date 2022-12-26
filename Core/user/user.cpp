#include "user.h"

QLatin1String User::USER_RIGHT_UNLOCK_DOOR = QLatin1String("unlock_door");

QLatin1String User::USER_ID = QLatin1String("user_id");
QLatin1String User::USER_DISPLAY_NAME = QLatin1String("display_name");
QLatin1String User::USER_RIGHTS = QLatin1String("rights");


User::User(QString id, QObject *parent) : QObject(parent), SerializableIdentifyable(id)
{

}

User::User(QSqlRecord record, QObject *parent) : QObject(parent), SerializableIdentifyable("")
{
    m_id = record.value(USER_ID).toString();
    m_displayName = record.value(USER_DISPLAY_NAME).toString();
    m_rights = record.value(USER_RIGHTS).toString().split(",");
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

QString User::displayName() {
    return m_displayName;
}

QStringList User::rights() {
    return m_rights;
}
