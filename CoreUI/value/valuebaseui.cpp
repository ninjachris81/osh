#include "valuebaseui.h"

ValueBaseUI::ValueBaseUI(Identifyable *parent) : VisualItemBase (parent)
{
    m_value = static_cast<ValueBase*>(parent);
    connect(m_value, &ValueBase::invalidated, this, &ValueBaseUI::isValidChanged);
    connect(m_value, &ValueBase::valueChanged, this, &ValueBaseUI::rawValueChanged);
    connect(m_value, &ValueBase::valueChanged, this, &ValueBaseUI::isValidChanged);
    connect(m_value, &ValueBase::signalRateChanged, this, &ValueBaseUI::signalRateChanged);
}

ValueBase* ValueBaseUI::parent() {
    return m_value;
}

void ValueBaseUI::updateValue(QVariant newValue) {
    m_value->updateValue(newValue);
}

QString ValueBaseUI::fullId() {
    return m_value->fullId();
}

bool ValueBaseUI::isValid() {
    return m_value->isValid();
}

QVariant ValueBaseUI::rawValue() {
    return m_value->rawValue();
}

VALUE_TYPE ValueBaseUI::valueType() {
    return m_value->valueType();
}

double ValueBaseUI::signalRate() {
    return m_value->signalRate();
}

QString ValueBaseUI::unitTypeSuffix() {
    return ValueBase::unitTypeToSuffix(m_value->unitType());
}
