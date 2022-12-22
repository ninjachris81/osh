#include "doorunlockmanager.h"

#include "macros.h"
#include "doorunlockmessage.h"

QLatin1String DoorUnlockManager::MANAGER_ID = QLatin1String("DoorUnlockManager");

DoorUnlockManager::DoorUnlockManager(QObject *parent) : ManagerBase(parent)
{

}

LogCat::LOGCAT DoorUnlockManager::logCat() {
    return LogCat::DOOR_UNLOCK;
}

QString DoorUnlockManager::id() {
    return MANAGER_ID;
}

void DoorUnlockManager::init(LocalConfig *config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(CommunicationManagerBase);

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);
}

MessageBase::MESSAGE_TYPE DoorUnlockManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_ACTOR;
}

void DoorUnlockManager::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
    DoorUnlockMessage* duMessage = static_cast<DoorUnlockMessage*>(msg);

    //duMessage->userId()
}
