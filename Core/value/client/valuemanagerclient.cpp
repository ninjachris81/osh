#include "valuemanagerclient.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

#include "macros.h"

ValueManagerClient::ValueManagerClient(QObject *parent) : ValueManagerBase(parent)
{

}

void ValueManagerClient::init(LocalConfig *config) {
    REQUIRE_MANAGER(CommunicationManagerBase);
}

void ValueManagerClient::handleReceivedMessage(ValueMessage* msg) {
    qDebug() << Q_FUNC_INFO;
}
