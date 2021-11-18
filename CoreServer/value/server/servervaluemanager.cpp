#include "value/server/servervaluemanager.h"

#include <QDebug>
#include <QDateTime>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

#include "macros.h"

ServerValueManager::ServerValueManager(QObject *parent) : ValueManagerBase(parent)
{
    connect(&m_valueCheckTimer, &QTimer::timeout, this, &ServerValueManager::checkValues);
}

void ServerValueManager::init(LocalConfig *config) {
    REQUIRE_MANAGER(CommunicationManagerBase);

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
    }
}

void ServerValueManager::valueReceived(QString valueGroupId, QString valueId, QVariant newValue) {
    ValueBase* value = getValue(valueGroupId, valueId);
    valueReceived(value, newValue);
}

/*
 * Check values for invalidation
*/
void ServerValueManager::checkValues() {
    //iDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ValueBase*> it(m_values);
    while(it.hasNext()) {
        it.next();

        if (it.value()->isValid() && it.value()->valueTimeout() > ValueBase::VALUE_TIMEOUT_NONE && QDateTime::currentMSecsSinceEpoch() - it.value()->lastUpdate() > it.value()->valueTimeout()) {
            invalidateValue((it.value()));
        }
    }
}

void ServerValueManager::invalidateValue(ValueBase* value) {
    value->invalidate();
    publishValue(value);
}

