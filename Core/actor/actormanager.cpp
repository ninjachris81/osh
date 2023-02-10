#include "actormanager.h"

#include <QDebug>

#include "actor/actormessage.h"
#include "value/client/clientvaluemanager.h"
#include "macros.h"

QLatin1String ActorManager::MANAGER_ID = QLatin1String("ActorManager");

ActorManager::ActorManager(QObject *parent) : ManagerBase(parent)
{
}

LogCat::LOGCAT ActorManager::logCat() {
    return LogCat::ACTOR;
}

void ActorManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

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
    ActorMessage* actorMessage = static_cast<ActorMessage*>(msg);
    iDebug() << Q_FUNC_INFO << actorMessage->fullId() << actorMessage->cmd();

    if (m_actors.contains(actorMessage->fullId())) {
        ActorBase* actor = m_actors.value(actorMessage->fullId());
        actor->triggerCmd(actorMessage->cmd(), "Message received");

        if (!actor->isAsync()) {        // only publish if value is set synchronously
            iDebug() << "Publish value";
            getManager<ClientValueManager>(ClientValueManager::MANAGER_ID)->publishValue(actor);
        }
    } else {
        iWarning() << "Invalid actor" << actorMessage->fullId();
    }
}

void ActorManager::registerActor(ActorBase* actor, ValueManagerBase *valueManager) {
    qDebug() << Q_FUNC_INFO << actor->fullId();

    m_actors.insert(actor->fullId(), actor);
    /*
    Q_ASSERT(connect(actor, &ActorBase::cmdTriggered, this, [this, actor](actor::ACTOR_CMDS cmd) {
        // TODO
    }) != nullptr);
    */

    valueManager->registerValue(actor);
}

void ActorManager::publishCmd(ActorBase *actor, actor::ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << actor->fullId();

    ActorMessage msg(actor->valueGroup()->id(), actor->id(), cmd);
    m_commManager->sendMessage(msg);
}

/*
void ActorManager::onCmdTriggered(ActorBase* actor, actor::ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    ActorMessage msg(actor->valueGroup()->id(), actor->id(), cmd);
    m_commManager->sendMessage(msg);
}
*/

ActorBase* ActorManager::getActor(QString fullId) {
    return m_actors.value(fullId);
}

QList<ActorBase*> ActorManager::actors() {
    return m_actors.values();
}
