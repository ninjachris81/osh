#include "doorunlockmessage.h"

QLatin1String DoorUnlockMessage::DU_ATTRIB_STAGE = QLatin1String("stage");
QLatin1String DoorUnlockMessage::DU_ATTRIB_TS = QLatin1String("ts");
QLatin1String DoorUnlockMessage::DU_ATTRIB_OTH = QLatin1String("oth");
QLatin1String DoorUnlockMessage::DU_ATTRIB_RESULT_HASH = QLatin1String("rh");


DoorUnlockMessage::DoorUnlockMessage(QString userId, QVariantMap values, QObject *parent) : MessageBase(parent), m_userId(userId), m_values(values)
{

}

MessageBase::MESSAGE_TYPE DoorUnlockMessage::getMessageType() {
    return MESSAGE_TYPE_DOOR_UNLOCK;
}

QString DoorUnlockMessage::getFirstLevelId() {
    return m_userId;
}

QString DoorUnlockMessage::getSecondLevelId() {
    return "";
}

QString DoorUnlockMessage::userId() {
    return m_userId;
}

QVariantMap DoorUnlockMessage::values() {
    return m_values;
}
