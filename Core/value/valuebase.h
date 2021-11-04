#ifndef VALUEBASE_H
#define VALUEBASE_H

#include <QObject>
#include <QVariant>

#include "valuegroup.h"
#include "identifyable.h"

class ValueBase : public Identifyable
{
Q_OBJECT

public:
    enum VALUE_TIMEOUT {
        VALUE_TIMEOUT_NONE,
        VALUE_TIMEOUT_SHORT = 5000,
        VALUE_TIMEOUT_MID = 30000,
        VALUE_TIMEOUT_LONG = 120000
    } m_valueTimeout = VALUE_TIMEOUT_NONE;

    explicit ValueBase(ValueGroup* valueGroup, QString id, QObject *parent = nullptr);

    ValueBase* withValueTimeout(VALUE_TIMEOUT timeout);

    static QString getFullId(QString valueGroupId, QString valueId);

    void setRawValue(QVariant value);

    void updateValue(QVariant newValue);

    virtual QVariant _updateValue(QVariant newValue) = 0;

    bool isValid() {
        return m_value.isValid();
    }

    QString fullId();
    ValueGroup* valueGroup();

    QVariant rawValue();

    qint64 lastUpdate();
    VALUE_TIMEOUT valueTimeout();

    void invalidate();

protected:

private:
    ValueGroup* m_valueGroup;
    QVariant m_value;
    qint64 m_lastUpdate = 0;

signals:
    void valueChanged();

};

#endif // VALUEBASE_H
