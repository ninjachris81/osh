#include "valuemanagerui.h"
#include "communication/communicationmanagerbase.h"

#include <QDebug>
#include "macros.h"

ValueManagerUI::ValueManagerUI(QObject *parent) : ValueManagerBase(parent)
{

}

void ValueManagerUI::init(LocalConfig *config) {
    REQUIRE_MANAGER(CommunicationManagerBase);
}

void ValueManagerUI::handleReceivedMessage(ValueMessage* msg) {
    qDebug() << Q_FUNC_INFO;
}
