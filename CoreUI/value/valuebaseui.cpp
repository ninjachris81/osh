#include "valuebaseui.h"

ValueBaseUI::ValueBaseUI(QObject *parent) : IdentifyableUI (parent)
{
    m_value = static_cast<ValueBase*>(parent);
    connect(m_value, &ValueBase::invalidated, this, &ValueBaseUI::isValidChanged);
    connect(m_value, &ValueBase::valueChanged, this, &ValueBaseUI::rawValueChanged);
    connect(m_value, &ValueBase::valueChanged, this, &ValueBaseUI::isValidChanged);
    connect(m_value, &ValueBase::signalRateChanged, this, &ValueBaseUI::signalRateChanged);
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

double ValueBaseUI::signalRate() {
    return m_value->signalRate();
}
