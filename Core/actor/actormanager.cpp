#include "actormanager.h"

#include <QDebug>

#include "actormessage.h"
#include "value/valuemanager.h"
#include "macros.h"


QString ActorManager::MANAGER_NAME = QStringLiteral("ActorManager");

ActorManager::ActorManager(QObject *parent) : ManagerBase(parent)
{

}

void ActorManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ValueManager);
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
