#ifndef REDUNDANTVALUE_H
#define REDUNDANTVALUE_H

#include <QObject>
#include <QList>
#include "value/valuebase.h"

class RedundantValue : public ValueBase
{
    Q_OBJECT
public:
    explicit RedundantValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit = true, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

    void addNextValue(ValueBase* value);

private:
    QList<ValueBase*> m_values;

signals:

public slots:
};

#endif // REDUNDANTVALUE_H
