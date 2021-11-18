#include "valuebase.h"

#include "shared/constants.h"

#include <QDebug>
#include <QDateTime>

ValueBase::ValueBase(ValueGroup *valueGroup, QString id, bool alwaysEmit, QObject *parent) : Identifyable (id, parent), m_valueGroup(valueGroup), m_alwaysEmit(alwaysEmit)
{
    Q_ASSERT(m_valueGroup != nullptr);
}

QString ValueBase::fullId() {
    return getFullId(m_valueGroup->id(), id());
}

ValueBase* ValueBase::withValueTimeout(VALUE_TIMEOUT timeout) {
    m_valueTimeout = timeout;
    return this;
}

QVariant ValueBase::rawValue() {
    return this->m_value;
}

ValueGroup* ValueBase::valueGroup() {
    return m_valueGroup;
}

void ValueBase::setRawValue(QVariant value) {
    switch(value.type()) {
    case QVariant::Int:
    case QVariant::Double:
    case QVariant::Bool:
    case QVariant::String:

        break;
    default:
        iWarning() << "Unsupported data type" << value.typeName();
        break;
    }
}

void ValueBase::updateValue(QVariant newValue) {
    iDebug() << Q_FUNC_INFO << newValue;

    m_value = _updateValue(newValue);
    bool hasChanged = m_value == newValue;
    m_lastUpdate = QDateTime::currentMSecsSinceEpoch();
    if (m_alwaysEmit || hasChanged) Q_EMIT(valueChanged());
}

QString ValueBase::getFullId(QString valueGroupId, QString valueId) {
    return valueGroupId + VALUE_SEPARATOR + valueId;
}

qint64 ValueBase::lastUpdate() {
    return m_lastUpdate;
}

ValueBase::VALUE_TIMEOUT ValueBase::valueTimeout() {
    return m_valueTimeout;
}

void ValueBase::invalidate() {
    iDebug() << Q_FUNC_INFO << fullId();

    m_value = QVariant();
    Q_EMIT(invalidated());
}
