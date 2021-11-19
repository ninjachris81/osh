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
    iDebug() << Q_FUNC_INFO;

    valueReceived(msg->valueGroupId(), msg->valueId(), msg->rawValue());
}

void ValueManagerUI::valueReceived(ValueBase* value, QVariant newValue) {
    if (value != nullptr) {
        value->updateValue(newValue);
    }
}

void ValueManagerUI::valueReceived(QString valueGroupId, QString valueId, QVariant newValue) {
    ValueBase* value = getValue(valueGroupId, valueId);
    valueReceived(value, newValue);
}
