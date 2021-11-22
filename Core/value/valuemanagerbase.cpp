#include "valuemanagerbase.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

QLatin1Literal ValueManagerBase::MANAGER_ID = QLatin1Literal("ValueManager");

ValueManagerBase::ValueManagerBase(QObject *parent) : ManagerBase(parent)
{
    connect(&m_signalRateTimer, &QTimer::timeout, this, &ValueManagerBase::updateSignalRates);
    m_signalRateTimer.start(10000);
}

QString ValueManagerBase::id() {
    return MANAGER_ID;
}

LogCat::LOGCAT ValueManagerBase::logCat() {
    return LogCat::VALUE;
}

void ValueManagerBase::publishValue(ValueBase* value) {
    iDebug() << Q_FUNC_INFO << value->fullId();

    CommunicationManagerBase* commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);
    ValueMessage valueMessage(value->valueGroup()->id(), value->id(), value->rawValue());
    commManager->sendMessage(valueMessage);
}

void ValueManagerBase::registerValue(ValueBase* value) {
    iDebug() << Q_FUNC_INFO << value->fullId();

    if (!m_knownValues.contains(value->fullId())) {
        m_knownValues.insert(value->fullId(), value);
    } else {
        iWarning() << "Value already registered" << value->fullId();
    }
}


ValueBase* ValueManagerBase::getValue(QString valueGroupId, QString valueId) {
    return getValue(ValueBase::getFullId(valueGroupId, valueId));
}

ValueBase* ValueManagerBase::getValue(QString fullId) {
    if (m_knownValues.contains(fullId)) {
        return m_knownValues.value(fullId);
    } else {
        return nullptr;
    }
}

MessageBase::MESSAGE_TYPE ValueManagerBase::getMessageType() {
    return MessageBase::MESSAGE_TYPE_VALUE;
}

void ValueManagerBase::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;

    ValueMessage* valueMessage = static_cast<ValueMessage*>(msg);
    handleReceivedMessage(valueMessage);
}

void ValueManagerBase::updateSignalRates() {
    iDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ValueBase*> it(m_knownValues);

    while(it.hasNext()) {
        it.next();
        it.value()->updateSignalRate();
    }

}
