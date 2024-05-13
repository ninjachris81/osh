#include "value/server/servervaluemanager.h"

#include <QDebug>
#include <QDateTime>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

#include "macros.h"
#include "helpers.h"

QLatin1String ServerValueManager::VALUE_PREFIX = QLatin1String("values");

ServerValueManager::ServerValueManager(QObject *parent) : ValueManagerBase(parent)
{
    connect(&m_valueCheckTimer, &QTimer::timeout, this, &ServerValueManager::checkValues);
}

void ServerValueManager::init(LocalConfig *config) {
    ValueManagerBase::init(config);

    REQUIRE_MANAGER(SimpleDatabaseManager);

    m_simpleDatabaseManager = getManager<SimpleDatabaseManager>(SimpleDatabaseManager::MANAGER_ID);

    Helpers::safeConnect(m_commManager, &CommunicationManagerBase::connected, this, &ServerValueManager::onConnected, SIGNAL(connected()), SLOT(onConnected()));

    m_valueCheckTimer.setInterval(config->getInt("value.checkInterval", 1000));
    m_valueCheckTimer.start();
}

void ServerValueManager::handleReceivedMessage(ValueMessage* msg) {
    iDebug() << Q_FUNC_INFO;

    valueReceived(msg->valueGroupId(), msg->valueId(), msg->rawValue());
}

void ServerValueManager::valueReceived(ValueBase* value, QVariant newValue) {
    if (value != nullptr) {
        value->updateValue(newValue);
        if (value->persist() && newValue.isValid()) {
            m_simpleDatabaseManager->simpleSet(VALUE_PREFIX, value->fullId(), newValue);
        }
    }
}

void ServerValueManager::valueReceived(QString valueGroupId, QString valueId, QVariant newValue) {
    ValueBase* value = getValue(valueGroupId, valueId);
    if (value != nullptr) {
        valueReceived(value, newValue);
    } else {
        iWarning() << " Value not registered" << valueGroupId << valueId;
    }
}

/*
 * Check values for invalidation
*/
void ServerValueManager::checkValues() {
    //iDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ValueBase*> it(m_knownValues);
    while(it.hasNext()) {
        it.next();

        if (it.value()->isValid() && it.value()->valueTimeout() > ValueBase::VT_NONE && QDateTime::currentMSecsSinceEpoch() - it.value()->lastUpdate() > it.value()->valueTimeout()) {
            invalidateValue((it.value()));
        }
    }
}


void ServerValueManager::invalidateValue(ValueBase* value) {
    value->invalidate();
    publishValue(value);
}

void ServerValueManager::onConnected() {
    iInfo() << Q_FUNC_INFO;

    QMapIterator<QString, ValueBase*> it(m_knownValues);
    while(it.hasNext()) {
        it.next();
        if (it.value()->persist()) {
            QVariant storedValue = m_simpleDatabaseManager->simpleGet(VALUE_PREFIX, it.key(), it.value()->typeHint());
            if (storedValue.isValid()) {
                iInfo() << "Publishing stored value" << it.key() << it.value();
                ValueBase* value = m_knownValues.value(it.key());
                value->updateValue(storedValue);
                publishValue(value);
            }
        }
    }
}

