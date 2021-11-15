#include "clientvaluemanager.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

#include "macros.h"

ClientValueManager::ClientValueManager(QObject *parent) : ValueManagerBase(parent)
{

}

void ClientValueManager::init(LocalConfig *config) {
    REQUIRE_MANAGER(CommunicationManagerBase);
}

void ClientValueManager::handleReceivedMessage(ValueMessage* msg) {
    qDebug() << Q_FUNC_INFO;
}
