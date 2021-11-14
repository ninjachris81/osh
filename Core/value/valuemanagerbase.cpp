#include "valuemanagerbase.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

QString ValueManagerBase::MANAGER_NAME = QStringLiteral("ValueManager");

ValueManagerBase::ValueManagerBase(QObject *parent) : ManagerBase(parent)
{

}

QString ValueManagerBase::getName() {
    return MANAGER_NAME;
}

void ValueManagerBase::publishValue(ValueBase* value) {
    qDebug() << Q_FUNC_INFO << value->fullId();

    CommunicationManagerBase* commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_NAME);
    ValueMessage valueMessage(value->valueGroup()->id(), value->id(), value->rawValue());
    commManager->sendMessage(valueMessage);
}

void ValueManagerBase::registerValue(ValueBase* value) {
    qDebug() << Q_FUNC_INFO << value->fullId();

    if (!m_values.contains(value->fullId())) {
        m_values.insert(value->fullId(), value);
    } else {
        qWarning() << "Value already registered" << value->fullId();
    }
}

ValueBase* ValueManagerBase::getValue(QString valueGroupId, QString valueId) {
    return getValue(ValueBase::getFullId(valueGroupId, valueId));
}

ValueBase* ValueManagerBase::getValue(QString fullId) {
    return m_values.value(fullId);
}

MessageBase::MESSAGE_TYPE ValueManagerBase::getMessageType() {
    return MessageBase::MESSAGE_TYPE_VALUE;
}

void ValueManagerBase::handleReceivedMessage(MessageBase* msg) {
    qDebug() << Q_FUNC_INFO;

    ValueMessage* valueMessage = static_cast<ValueMessage*>(msg);
    handleReceivedMessage(valueMessage);
}
