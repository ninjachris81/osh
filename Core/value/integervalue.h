#ifndef INTEGERVALUE_H
#define INTEGERVALUE_H

#include <QObject>
#include "valuebase.h"

class IntegerValue : public ValueBase
{
    Q_OBJECT
public:
    explicit IntegerValue(ValueGroup *valueGroup, QString id, UNIT_TYPE unitType, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // INTEGERVALUE_H
