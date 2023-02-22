#include "valuemanagerbase.h"

#include <QDebug>

#include "value/valuemessage.h"

QLatin1String ValueManagerBase::MANAGER_ID = QLatin1String("ValueManager");

ValueManagerBase::ValueManagerBase(QObject *parent) : ManagerBase(parent)
{
}

QString ValueManagerBase::id() {
    return MANAGER_ID;
}

void ValueManagerBase::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(CommunicationManagerBase);
    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);

    if (managerRegistration()->instanceRole() == ManagerRegistration::GUI) {
        connect(&m_signalRateTimer, &QTimer::timeout, this, &ValueManagerBase::onUpdateSignalRates);
        m_signalRateTimer.start(10000);
    }
}

LogCat::LOGCAT ValueManagerBase::logCat() {
    return LogCat::VALUE;
}

void ValueManagerBase::publishValue(ValueBase* value) {
    iDebug() << Q_FUNC_INFO << value->fullId();

    ValueMessage valueMessage(value->valueGroup()->id(), value->id(), value->rawValue());
    m_commManager->sendMessage(valueMessage);
}

void ValueManagerBase::registerValue(ValueBase* value) {
    iDebug() << Q_FUNC_INFO << value->fullId();

    if (!m_knownValues.contains(value->fullId())) {
        m_knownValues.insert(value->fullId(), value);
        value->connectManager(this);
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

ValueBase* ValueManagerBase::getValue(ValueGroup *valueGroup, QString valueId) {
    return getValue(valueGroup->id(), valueId);
}

MessageBase::MESSAGE_TYPE ValueManagerBase::getMessageType() {
    return MessageBase::MESSAGE_TYPE_VALUE;
}

void ValueManagerBase::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;

    ValueMessage* valueMessage = static_cast<ValueMessage*>(msg);
    handleReceivedMessage(valueMessage);
}

void ValueManagerBase::onUpdateSignalRates() {
    iDebug() << Q_FUNC_INFO;

    Q_EMIT(updateSignalRates());
}
