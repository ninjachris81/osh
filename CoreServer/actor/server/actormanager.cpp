#include "actormanager.h"

#include <QDebug>

#include "actor/actormessage.h"
#include "value/valuemanagerbase.h"
#include "macros.h"

QLatin1Literal ActorManager::MANAGER_ID = QLatin1Literal("ActorManager");

ActorManager::ActorManager(QObject *parent) : ManagerBase(parent)
{

}

LogCat::LOGCAT ActorManager::logCat() {
    return LogCat::ACTOR;
}

void ActorManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ValueManagerBase);
    REQUIRE_MANAGER(CommunicationManagerBase);

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);
}

QString ActorManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE ActorManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_ACTOR;
}

void ActorManager::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
    ActorMessage* actorMessage = static_cast<ActorMessage*>(msg);

    switch(actorMessage->cmd()) {

    }
}

void ActorManager::registerActor(ActorBase* actor) {
    m_actors.insert(actor->id(), actor);
    connect(actor, &ActorBase::cmdTriggered, this, [this, actor](ACTOR_CMDS cmd) {
        this->onCmdTriggered(actor, cmd);
    });
}

void ActorManager::onCmdTriggered(ActorBase* actor, ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    ActorMessage msg(actor->valueGroup()->id(), actor->id(), cmd);
    m_commManager->sendMessage(msg);
}
