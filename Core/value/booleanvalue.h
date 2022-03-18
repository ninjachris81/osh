#ifndef BOOLEANVALUE_H
#define BOOLEANVALUE_H

#include <QObject>
#include "valuebase.h"

class BooleanValue : public ValueBase
{
    Q_OBJECT
public:
    BooleanValue();
    explicit BooleanValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // BOOLEANVALUE_H
