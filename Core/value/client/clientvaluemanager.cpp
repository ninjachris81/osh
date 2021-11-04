#include "clientvaluemanager.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

#include "macros.h"

QString ClientValueManager::MANAGER_NAME = QStringLiteral("ClientValueManager");

ClientValueManager::ClientValueManager(QObject *parent) : ValueManagerBase(parent)
{

}

void ClientValueManager::init(LocalConfig *config) {
    REQUIRE_MANAGER(CommunicationManagerBase);
}

QString ClientValueManager::getName() {
    return MANAGER_NAME;
}

MessageBase::MESSAGE_TYPE ClientValueManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_VALUE;
}

void ClientValueManager::handleReceivedMessage(MessageBase* msg) {
    qDebug() << Q_FUNC_INFO;

    ValueMessage* valueMessage = static_cast<ValueMessage*>(msg);
}
