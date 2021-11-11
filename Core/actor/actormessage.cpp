#include "actormessage.h"

ActorMessage::ActorMessage(QString actorGroupId, QString actorId, ACTOR_CMDS cmd, QObject *parent) : MessageBase(parent), m_actorGroupId(actorGroupId), m_actorId(actorId), m_cmd(cmd)
{

}

MessageBase::MESSAGE_TYPE ActorMessage::getMessageType() {
    return MESSAGE_TYPE_ACTOR;
}

QString ActorMessage::getFirstLevelId() {
    return m_actorGroupId;
}

QString ActorMessage::getSecondLevelId() {
    return m_actorId;
}

QString ActorMessage::actorGroupId() {
    return m_actorGroupId;
}

QString ActorMessage::actorId() {
    return m_actorId;
}

ACTOR_CMDS ActorMessage::cmd() {
    return m_cmd;
}

QString ActorMessage::fullId() {
    return m_actorGroupId + VALUE_SEPARATOR + m_actorId;
}
