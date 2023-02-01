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
    REQUIRE_MANAGER(CommunicationManagerBase);
}

void ClientValueManager::handleReceivedMessage(ValueMessage* msg) {
    iDebug() << Q_FUNC_INFO;
}

void ClientValueManager::registerValue(ValueBase* value) {
    ValueManagerBase::registerValue(value);

    Q_ASSERT(QObject::connect(value, &ValueBase::valueChanged, [value, this]() {
        this->publishValue(value);
    }) != nullptr);
}

void ClientValueManager::maintainValues() {
    QMapIterator<QString, ValueBase*> it(m_knownValues);

    while(it.hasNext()) {
        it.next();
        if (it.value()->checkMaintenance()) {
            iDebug() << "Maintain value" << it.key();
            publishValue(it.value());
        }
    }
}
