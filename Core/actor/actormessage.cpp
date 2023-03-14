#include "actormessage.h"

ActorMessage::ActorMessage(QString actorGroupId, QString actorId, QVariant rawValue, ACTOR_CMDS cmd, QObject *parent) :
    ValueMessage(actorGroupId, actorId, rawValue), m_cmd(cmd)
{

}

MessageBase::MESSAGE_TYPE ActorMessage::getMessageType() {
    return MESSAGE_TYPE_ACTOR;
}

ACTOR_CMDS ActorMessage::cmd() {
    return m_cmd;
}
