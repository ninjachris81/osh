#include "clientactormanager.h"

#include <QDebug>

#include "actor/actormessage.h"
#include "value/client/clientvaluemanager.h"
#include "macros.h"

QString ClientActorManager::MANAGER_NAME = QStringLiteral("ClientActorManager");

ClientActorManager::ClientActorManager(QObject *parent) : ManagerBase(parent)
{

}

void ClientActorManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ClientValueManager);
}

QString ClientActorManager::getName() {
    return MANAGER_NAME;
}

MessageBase::MESSAGE_TYPE ClientActorManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_ACTOR;
}

void ClientActorManager::handleReceivedMessage(MessageBase* msg) {
    ActorMessage* actorMessage = static_cast<ActorMessage*>(msg);
    qDebug() << Q_FUNC_INFO << actorMessage->fullId() << actorMessage->cmd();

    if (m_actors.contains(actorMessage->fullId())) {
        ActorBase* actor = m_actors.value(actorMessage->fullId());
        actor->triggerCmd(actorMessage->cmd());

        if (!actor->isAsync()) {        // only publish if value is set synchronously
            qDebug() << "Publish value";
            getManager<ClientValueManager>(ClientValueManager::MANAGER_NAME)->publishValue(actor);
        }
    } else {
        qWarning() << "Invalid actor" << actorMessage->fullId();
    }
}

void ClientActorManager::registerActor(ActorBase* actor) {
    qDebug() << Q_FUNC_INFO << actor->fullId();
    m_actors.insert(actor->fullId(), actor);
}
