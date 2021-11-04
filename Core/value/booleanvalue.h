#ifndef BOOLEANVALUE_H
#define BOOLEANVALUE_H

#include <QObject>
#include "valuebase.h"

class BooleanValue : public ValueBase
{
    Q_OBJECT
public:
    explicit BooleanValue(ValueGroup *valueGroup, QString id, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

signals:

public slots:
};

#endif // BOOLEANVALUE_H
