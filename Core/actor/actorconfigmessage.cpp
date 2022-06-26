#include "actorconfigmessage.h"

ActorConfigMessage::ActorConfigMessage(QString actorGroupId, QString actorId, QMap<QString, QVariant> values, QObject *parent)
    : MessageBase(parent), m_actorGroupId(actorGroupId), m_actorId(actorId), m_values(values)
{

}

MessageBase::MESSAGE_TYPE ActorConfigMessage::getMessageType() {
    return MESSAGE_TYPE_ACTOR_CONFIG;
}

QString ActorConfigMessage::getFirstLevelId() {
    return m_actorGroupId;
}

QString ActorConfigMessage::getSecondLevelId() {
    return m_actorId;
}

QString ActorConfigMessage::actorGroupId() {
    return m_actorGroupId;
}

QString ActorConfigMessage::actorId() {
    return m_actorId;
}

QString ActorConfigMessage::fullId() {
    return m_actorGroupId + VALUE_SEPARATOR + m_actorId;
}

QMap<QString, QVariant> ActorConfigMessage::values() {
    return m_values;
}
