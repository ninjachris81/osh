#ifndef DOUBLEVALUE_H
#define DOUBLEVALUE_H

#include <QObject>
#include "valuebase.h"

class DoubleValue : public ValueBase
{
    Q_OBJECT
public:
    DoubleValue();
    explicit DoubleValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // DOUBLEVALUE_H
