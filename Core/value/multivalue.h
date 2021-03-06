#ifndef MULTIVALUE_H
#define MULTIVALUE_H

#include <QObject>
#include "valuebase.h"

class MultiValue : public ValueBase
{
    Q_OBJECT
public:
    MultiValue();
    explicit MultiValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

};

#endif // MULTIVALUE_H
