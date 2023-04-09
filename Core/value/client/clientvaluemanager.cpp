#include "clientvaluemanager.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

#include "macros.h"

#include "helpers.h"

ClientValueManager::ClientValueManager(QObject *parent) : ValueManagerBase(parent)
{
    connect(&m_maintenanceTimer, &QTimer::timeout, this, &ClientValueManager::maintainValues);
    m_maintenanceTimer.start(1000);
}

void ClientValueManager::init(LocalConfig *config) {
    ValueManagerBase::init(config);
}

void ClientValueManager::handleReceivedMessage(ValueMessage* msg) {
    iDebug() << Q_FUNC_INFO;

    if (m_notificationValues.contains(msg->fullId())) {
        ValueBase* value = getValue(msg->valueGroupId(), msg->valueId());
        value->updateValue(msg->rawValue());
    } else {
        iDebug() << "Ignoring update of value" << msg->fullId();
    }
}

void ClientValueManager::registerValue(ValueBase* value) {
    qDebug() << Q_FUNC_INFO << value->fullId();

    ValueManagerBase::registerValue(value);

    //Helpers::safeConnect(value, &ValueBase::valueChanged, this, &ClientValueManager::_onValueChanged, SIGNAL(valueChanged), SLOT(onValueChanged));
}

void ClientValueManager::registerForMaintenance(ValueBase* value) {
    iInfo() << Q_FUNC_INFO << value->fullId();
    m_maintenanceValues.insert(value->fullId(), value);
}

void ClientValueManager::registerForNotification(ValueBase* value) {
    iInfo() << Q_FUNC_INFO << value->fullId();
    m_notificationValues.insert(value->fullId(), value);
}


void ClientValueManager::maintainValues() {
    QMapIterator<QString, ValueBase*> it(m_maintenanceValues);

    while(it.hasNext()) {
        it.next();
        if (it.value()->checkMaintenance()) {
            iDebug() << "Maintain value" << it.key();
            publishValue(it.value());
        }
    }
}

/*
void ClientValueManager::_onValueChanged() {
    qDebug() << Q_FUNC_INFO;

    ValueBase* value = qobject_cast<ValueBase*>(sender());
    this->publishValue(value);
}
*/
