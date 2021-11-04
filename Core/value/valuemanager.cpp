#include "valuemanager.h"

#include <QDebug>
#include <QDateTime>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

#include "macros.h"

QString ValueManager::MANAGER_NAME = QStringLiteral("ValueManager");

ValueManager::ValueManager(QObject *parent) : ValueManagerBase(parent)
{
    connect(&m_valueCheckTimer, &QTimer::timeout, this, &ValueManager::checkValues);
}

void ValueManager::init(LocalConfig *config) {
    REQUIRE_MANAGER(CommunicationManagerBase);

    m_valueCheckTimer.setInterval(config->getInt("value.checkInterval", 1000));
    m_valueCheckTimer.start();
}

QString ValueManager::getName() {
    return MANAGER_NAME;
}

void ValueManager::registerValue(ValueBase* value) {
    qDebug() << Q_FUNC_INFO << value->fullId();

    if (!m_values.contains(value->fullId())) {
        m_values.insert(value->fullId(), value);
    } else {
        qWarning() << "Value already registered" << value->fullId();
    }
}

MessageBase::MESSAGE_TYPE ValueManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_VALUE;
}

void ValueManager::handleReceivedMessage(MessageBase* msg) {
    qDebug() << Q_FUNC_INFO;

    ValueMessage* valueMessage = static_cast<ValueMessage*>(msg);
    updateValue(valueMessage->valueGroupId(), valueMessage->valueId(), valueMessage->rawValue());
}

ValueBase* ValueManager::getValue(QString valueGroupId, QString valueId) {
    return getValue(ValueBase::getFullId(valueGroupId, valueId));
}

ValueBase* ValueManager::getValue(QString fullId) {
    return m_values.value(fullId);
}

void ValueManager::updateValue(ValueBase* value, QVariant newValue) {
    if (value != nullptr) {
        value->updateValue(newValue);
    }
}

void ValueManager::updateValue(QString valueGroupId, QString valueId, QVariant newValue) {
    ValueBase* value = getValue(valueGroupId, valueId);
    updateValue(value, newValue);
}

void ValueManager::checkValues() {
    //qDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ValueBase*> it(m_values);
    while(it.hasNext()) {
        it.next();

        if (it.value()->isValid() && it.value()->valueTimeout() > ValueBase::VALUE_TIMEOUT_NONE && QDateTime::currentMSecsSinceEpoch() - it.value()->lastUpdate() > it.value()->valueTimeout()) {
            invalidateValue((it.value()));
        }
    }
}

void ValueManager::invalidateValue(ValueBase* value) {
    value->invalidate();
    publishValue(value);
}

