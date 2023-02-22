#ifndef INTEGERVALUE_H
#define INTEGERVALUE_H

#include <QObject>

#include "sharedlib.h"

#include "valuebase.h"

class SHARED_LIB_EXPORT IntegerValue : public ValueBase
{
    Q_OBJECT
public:
    IntegerValue();
    explicit IntegerValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit = true, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // INTEGERVALUE_H
