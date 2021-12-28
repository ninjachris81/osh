#ifndef LONGVALUE_H
#define LONGVALUE_H

#include <QObject>
#include "valuebase.h"

class LongValue : public ValueBase
{
    Q_OBJECT
public:
    explicit LongValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // LONGVALUE_H
