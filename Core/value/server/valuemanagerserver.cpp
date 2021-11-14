#include "value/server/valuemanagerserver.h"

#include <QDebug>
#include <QDateTime>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

#include "macros.h"

ValueManagerServer::ValueManagerServer(QObject *parent) : ValueManagerBase(parent)
{
    connect(&m_valueCheckTimer, &QTimer::timeout, this, &ValueManagerServer::checkValues);
}

void ValueManagerServer::init(LocalConfig *config) {
    REQUIRE_MANAGER(CommunicationManagerBase);

    m_valueCheckTimer.setInterval(config->getInt("value.checkInterval", 1000));
    m_valueCheckTimer.start();
}

void ValueManagerServer::handleReceivedMessage(ValueMessage* msg) {
    qDebug() << Q_FUNC_INFO;

    updateValue(msg->valueGroupId(), msg->valueId(), msg->rawValue());
}

void ValueManagerServer::updateValue(ValueBase* value, QVariant newValue) {
    if (value != nullptr) {
        value->updateValue(newValue);
    }
}

void ValueManagerServer::updateValue(QString valueGroupId, QString valueId, QVariant newValue) {
    ValueBase* value = getValue(valueGroupId, valueId);
    updateValue(value, newValue);
}

void ValueManagerServer::checkValues() {
    //qDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ValueBase*> it(m_values);
    while(it.hasNext()) {
        it.next();

        if (it.value()->isValid() && it.value()->valueTimeout() > ValueBase::VALUE_TIMEOUT_NONE && QDateTime::currentMSecsSinceEpoch() - it.value()->lastUpdate() > it.value()->valueTimeout()) {
            invalidateValue((it.value()));
        }
    }
}

void ValueManagerServer::invalidateValue(ValueBase* value) {
    value->invalidate();
    publishValue(value);
}

