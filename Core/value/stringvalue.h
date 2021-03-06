#ifndef STRINGVALUE_H
#define STRINGVALUE_H

#include <QObject>
#include "valuebase.h"

class StringValue : public ValueBase
{
    Q_OBJECT
public:
    explicit StringValue();
    explicit StringValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // STRINGVALUE_H
