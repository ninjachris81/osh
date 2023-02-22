#ifndef BOOLEANVALUE_H
#define BOOLEANVALUE_H

#include <QObject>

#include "sharedlib.h"

#include "valuebase.h"

class SHARED_LIB_EXPORT BooleanValue : public ValueBase
{
Q_OBJECT
public:
    explicit BooleanValue();
    explicit BooleanValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit = true, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // BOOLEANVALUE_H
