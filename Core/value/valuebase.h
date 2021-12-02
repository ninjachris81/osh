#ifndef VALUEBASE_H
#define VALUEBASE_H

#include <QObject>
#include <QVariant>

#include "valuegroup.h"
#include "identifyable.h"
#include "shared/units_qt.h"
#include "shared/value.h"

using namespace unit;

class ValueBase : public Identifyable
{
Q_OBJECT

public:
    enum VALUE_TIMEOUT {
        VT_NONE,
        VT_SHORT = VALUE_TIMEOUT_SHORT,
        VT_MID = VALUE_TIMEOUT_MID,
        VT_LONG = VALUE_TIMEOUT_LONG
    } m_valueTimeout = VT_NONE;

    explicit ValueBase(ValueGroup* valueGroup, QString id, UNIT_TYPE unitType = UT_UNKNOWN, bool alwaysEmit = true, QObject *parent = nullptr);

    ValueBase* withValueTimeout(VALUE_TIMEOUT timeout);

    static QString getFullId(QString valueGroupId, QString valueId);

    void setRawValue(QVariant value);

    void updateValue(QVariant newValue);

    virtual QVariant _updateValue(QVariant newValue) = 0;

    QString fullId();
    ValueGroup* valueGroup();

    Q_INVOKABLE QVariant rawValue();

    Q_INVOKABLE bool isValid() {
        return m_value.isValid();
    }

    UNIT_TYPE unitType();
    static QString unitTypeToSuffix(UNIT_TYPE unitType);

    qint64 lastUpdate();
    VALUE_TIMEOUT valueTimeout();

    int maintenanceInterval();
    bool checkMaintenance();

    void invalidate();

    double signalRate();

    void updateSignalRate();

protected:

private:
    ValueGroup* m_valueGroup;
    QVariant m_value;
    qint64 m_lastUpdate = 0;
    bool m_alwaysEmit = true;

    UNIT_TYPE m_unitType = UT_UNKNOWN;

    qint64 m_lastMaintenance = 0;

    double m_signalRate = 0;
    quint8 m_signalCount = 0;
    quint32 m_currentSignalCount = 0;

signals:
    void valueChanged();
    void invalidated();
    void signalRateChanged();

};

#endif // VALUEBASE_H
