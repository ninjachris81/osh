#ifndef LONGVALUE_H
#define LONGVALUE_H

#include <QObject>

#include "sharedlib.h"

#include "valuebase.h"

class SHARED_LIB_EXPORT LongValue : public ValueBase
{
    Q_OBJECT
public:
    LongValue();
    explicit LongValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // LONGVALUE_H
