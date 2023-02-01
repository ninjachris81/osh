#ifndef ENUMVALUE_H
#define ENUMVALUE_H

#include <QObject>

#include "sharedlib.h"

#include "integervalue.h"

class SHARED_LIB_EXPORT EnumValue : public IntegerValue
{
    Q_OBJECT
public:
    explicit EnumValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // ENUMVALUE_H
