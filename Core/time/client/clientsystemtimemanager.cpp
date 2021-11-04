#include "clientsystemtimemanager.h"

#include <QDebug>
#include "communication/communicationmanagerbase.h"
#include "time/systemtimemessage.h"

QString ClientSystemtimeManager::MANAGER_NAME = QStringLiteral("ClientSystemtimeManager");

ClientSystemtimeManager::ClientSystemtimeManager(QObject *parent) : ManagerBase(parent)
{

}

void ClientSystemtimeManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;
}

QString ClientSystemtimeManager::getName() {
    return MANAGER_NAME;
}

void ClientSystemtimeManager::setSystemTime(qint64 ts) {
    qDebug() << Q_FUNC_INFO;
    // TODO
}

MessageBase::MESSAGE_TYPE ClientSystemtimeManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_SYSTEM_TIME;
}

void ClientSystemtimeManager::handleReceivedMessage(MessageBase* msg) {
    qDebug() << Q_FUNC_INFO;
    SystemtimeMessage* systimeMessage = static_cast<SystemtimeMessage*>(msg);

    setSystemTime(systimeMessage->ts());
}
