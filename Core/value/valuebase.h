#ifndef VALUEBASE_H
#define VALUEBASE_H

#include <QObject>
#include <QVariant>

#include "sharedlib.h"

#include "valuegroup.h"
#include "serializableidentifyable.h"
#include "shared/units_qt.h"
#include "shared/value_qt.h"
#include "meta/itemmetainfo.h"
#include "meta/metainfosupport.h"

using namespace unit;
using namespace value;

class ValueManagerBase;

class SHARED_LIB_EXPORT ValueBase : public QObject, public SerializableIdentifyable, public MetaInfoSupport
{
Q_OBJECT

public:
    enum VALUE_TIMEOUT {
        VT_NONE,
        VT_SHORT = VALUE_TIMEOUT_SHORT,
        VT_MID = VALUE_TIMEOUT_MID,
        VT_LONG = VALUE_TIMEOUT_LONG
    } m_valueTimeout = VT_NONE;

    static QLatin1String PROPERTY_VALUE_TYPE;
    static QLatin1String PROPERTY_VALUE_TIMEOUT;
    static QLatin1String PROPERTY_ALWAYS_EMIT;
    static QLatin1String PROPERTY_PERSIST;

    ValueBase();
    explicit ValueBase(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit = true, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;

    ValueBase* withValueTimeout(VALUE_TIMEOUT timeout);

    ValueBase* withPersist(bool persist);

    ValueBase* withAlwaysEmit(bool alwaysEmit);

    bool persist();

    static QString getFullId(QString valueGroupId, QString valueId);

    bool updateValue(QVariant newValue, bool emitChange = true);

    virtual QVariant _updateValue(QVariant newValue) = 0;

    QString fullId();
    ValueGroup* valueGroup();
    void setValueGroup(ValueGroup* valueGroup);

    Q_INVOKABLE QVariant rawValue();

    Q_INVOKABLE bool isValid() {
        return m_value.isValid();
    }

    VALUE_TYPE valueType();
    UNIT_TYPE unitType();

    static QString unitTypeToSuffix(UNIT_TYPE unitType);
    static UNIT_TYPE valueTypeToUnitType(VALUE_TYPE valueType);

    qint64 lastUpdate();
    VALUE_TIMEOUT valueTimeout();

    int maintenanceInterval();
    bool checkMaintenance();

    void invalidate();

    double signalRate();

    void connectManager(ValueManagerBase* manager);

private slots:
    void onUpdateSignalRate();

protected:
    bool m_alwaysEmit = true;

private:
    VALUE_TYPE m_valueType;
    ValueGroup* m_valueGroup;
    QVariant m_value;
    qint64 m_lastUpdate = 0;
    bool m_persist = false;

    qint64 m_lastMaintenance = 0;

    double m_signalRate = 0;
    quint8 m_signalCount = 0;
    quint32 m_currentSignalCount = 0;

signals:
    void valueChanged();
    void invalidated();
    void signalRateChanged();

    void updateSignalRate();

};

#endif // VALUEBASE_H
