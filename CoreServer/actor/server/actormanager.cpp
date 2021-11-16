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
