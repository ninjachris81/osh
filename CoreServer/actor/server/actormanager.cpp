#include "actormanager.h"

#include <QDebug>

#include "actor/actormessage.h"
#include "value/valuemanagerbase.h"
#include "macros.h"

QString ActorManager::MANAGER_NAME = QStringLiteral("ActorManager");

ActorManager::ActorManager(QObject *parent) : ManagerBase(parent)
{

}

void ActorManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ValueManagerBase);
}

QString ActorManager::getName() {
    return MANAGER_NAME;
}

MessageBase::MESSAGE_TYPE ActorManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_ACTOR;
}

void ActorManager::handleReceivedMessage(MessageBase* msg) {
    qDebug() << Q_FUNC_INFO;
    ActorMessage* actorMessage = static_cast<ActorMessage*>(msg);

    switch(actorMessage->cmd()) {

    }
}
