#ifndef DOUBLEVALUE_H
#define DOUBLEVALUE_H

#include <QObject>

#include "sharedlib.h"

#include "valuebase.h"

class SHARED_LIB_EXPORT DoubleValue : public ValueBase
{
    Q_OBJECT
public:
    explicit DoubleValue();
    explicit DoubleValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // DOUBLEVALUE_H
