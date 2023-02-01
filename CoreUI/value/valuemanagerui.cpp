#include "valuemanagerui.h"
#include "communication/communicationmanagerbase.h"

#include <QDebug>
#include "macros.h"

ValueManagerUI * ValueManagerUI::m_qmlInstance = nullptr;

ValueManagerUI::ValueManagerUI(QObject *parent) : ValueManagerBase(parent)
{
    m_qmlInstance = this;
}

QObject* ValueManagerUI::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return m_qmlInstance;
}

void ValueManagerUI::init(LocalConfig *config) {
    ValueManagerBase::init(config);
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

QString ValueManagerUI::unitTypeToSuffix(unit::UNIT_TYPE unitType) {
    return ValueBase::unitTypeToSuffix((unitType));
}
