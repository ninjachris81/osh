#include "clientsystemtimemanager.h"

#include <QDebug>
#include "communication/communicationmanagerbase.h"
#include "time/systemtimemessage.h"

QLatin1Literal ClientSystemtimeManager::MANAGER_ID = QLatin1Literal("ClientSystemtimeManager");

ClientSystemtimeManager::ClientSystemtimeManager(QObject *parent) : ManagerBase(parent)
{

}

void ClientSystemtimeManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;
}

QString ClientSystemtimeManager::id() {
    return MANAGER_ID;
}

void ClientSystemtimeManager::setSystemTime(qint64 ts) {
    iDebug() << Q_FUNC_INFO;
    // TODO
}

MessageBase::MESSAGE_TYPE ClientSystemtimeManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_SYSTEM_TIME;
}

void ClientSystemtimeManager::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
    SystemtimeMessage* systimeMessage = static_cast<SystemtimeMessage*>(msg);

    setSystemTime(systimeMessage->ts());
}
