#include "valuebase.h"

#include "shared/constants.h"
#include "value/valuemanagerbase.h"

#include <QDebug>
#include <QDateTime>

QLatin1String ValueBase::PROPERTY_VALUE_TYPE = QLatin1String("value_type");
QLatin1String ValueBase::PROPERTY_VALUE_TIMEOUT = QLatin1String("value_timeout");
QLatin1String ValueBase::PROPERTY_ALWAYS_EMIT = QLatin1String("always_emit");
QLatin1String ValueBase::PROPERTY_PERSIST = QLatin1String("persist");
QLatin1String ValueBase::PROPERTY_TYPE_HINT = QLatin1String("type_hint");

ValueBase::ValueBase() : SerializableIdentifyable() {
}

ValueBase::ValueBase(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit, QVariant::Type typeHint, QObject *parent) : QObject(parent), SerializableIdentifyable (id),
    m_alwaysEmit(alwaysEmit), m_typeHint(typeHint), m_valueType(valueType), m_valueGroup(valueGroup)
{
    Q_ASSERT(m_valueGroup != nullptr);

    connect(this, &ValueBase::updateSignalRate, this, &ValueBase::onUpdateSignalRate);
}

void ValueBase::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);
    m_metaInfo.serialize(obj);

    obj.insert("valueType", m_valueType);
    obj.insert("alwaysEmit", m_alwaysEmit);
    obj.insert("valueGroupId", m_valueGroup->id());
}

void ValueBase::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);
    m_metaInfo.deserialize(obj);

    m_valueType = (VALUE_TYPE) obj.value("valueType").toInt();
    m_alwaysEmit = obj.value("alwaysEmit").toBool();
}

QString ValueBase::getClassName() {
    return metaObject()->className();
}

QString ValueBase::fullId() {
    return getFullId(m_valueGroup->id(), id());
}

ValueBase* ValueBase::withValueTimeout(VALUE_TIMEOUT timeout) {
    m_valueTimeout = timeout;
    return this;
}

ValueBase* ValueBase::withPersist(bool persist) {
    m_persist = persist;
    return this;
}

ValueBase* ValueBase::withAlwaysEmit(bool alwaysEmit) {
    m_alwaysEmit = alwaysEmit;
    return this;
}

bool ValueBase::persist() {
    return m_persist;
}

QVariant ValueBase::rawValue() {
    return this->m_value;
}

ValueGroup* ValueBase::valueGroup() {
    return m_valueGroup;
}

void ValueBase::setValueGroup(ValueGroup* valueGroup) {
    m_valueGroup = valueGroup;
}

bool ValueBase::updateValue(QVariant newValue, bool emitChange) {
    iDebug() << Q_FUNC_INFO << newValue << m_value;

    m_currentSignalCount++;

    bool isDifferent = (m_value != newValue);
    m_value = _updateValue(newValue);
    //bool newValueApplied = m_value == newValue;
    m_lastUpdate = QDateTime::currentMSecsSinceEpoch();
    if (emitChange && (m_alwaysEmit || isDifferent)) {
        iDebug() << "Value changed emit";
        Q_EMIT(valueChanged());
    }
    return isDifferent;
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

int ValueBase::maintenanceInterval() {
    if (m_valueTimeout == ValueBase::VT_NONE) {
        return -1;
    } else {
        return m_valueTimeout / 2;
    }
}

bool ValueBase::checkMaintenance() {
    if (!m_value.isValid()) return false;
    if (maintenanceInterval() <= 0) return false;
    if (QDateTime::currentMSecsSinceEpoch() > m_lastMaintenance + maintenanceInterval()) {
        m_lastMaintenance = QDateTime::currentMSecsSinceEpoch();
        return true;
    } else {
        return false;
    }
}

void ValueBase::invalidate() {
    iDebug() << Q_FUNC_INFO << fullId();

    m_value = QVariant();
    Q_EMIT(invalidated());
    onUpdateSignalRate();
}

double ValueBase::signalRate() {
    return m_signalRate;
}

void ValueBase::onUpdateSignalRate() {
    iDebug() << Q_FUNC_INFO;

    if (m_value.isValid()) {
        m_signalCount++;
        m_signalRate = 60 / qMax(m_signalCount * 10, 1) * qMax(m_currentSignalCount, (quint32)1);
        Q_EMIT(signalRateChanged());

        if (m_signalCount >= 6) {
            m_signalCount = 0;
            m_currentSignalCount = 0;
        }
    } else {
        m_signalRate = 0;
        Q_EMIT(signalRateChanged());
    }
}

void ValueBase::connectManager(ValueManagerBase* manager) {
    connect(manager, &ValueManagerBase::updateSignalRates, this, &ValueBase::onUpdateSignalRate);
}

VALUE_TYPE ValueBase::valueType() {
    return m_valueType;
}

UNIT_TYPE ValueBase::unitType() {
    return valueTypeToUnitType(m_valueType);
}

UNIT_TYPE ValueBase::valueTypeToUnitType(VALUE_TYPE valueType) {
    switch(valueType) {
    case VALUE_TYPE_BRIGHTNESS: return UT_PERCENT;
    case VALUE_TYPE_TEMP: return UT_DEGREES;
    case VALTYPE_HUMIDITY: return UT_PERCENT;
    case VALTYPE_WATER_FLOW: return UT_LITER_PER_MIN;
    case VALTYPE_WATER_LEVEL: return UT_LITERS;
    case VALTYPE_TIMESTAMP: return UT_TIMESTAMP;
    default: return UT_UNKNOWN;
    }
}

QString ValueBase::unitTypeToSuffix(UNIT_TYPE unitType) {
    switch(unitType) {
    case UT_UNKNOWN: return "";
    case UT_DEGREES: return "°";
    case UT_PERCENT: return "%";
    case UT_TIMESTAMP: return "";
    case UT_LITER_PER_MIN: return "l/min";
    case UT_LITERS: return "l";
    }
}
