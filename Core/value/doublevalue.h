#ifndef DOUBLEVALUE_H
#define DOUBLEVALUE_H

#include <QObject>
#include "valuebase.h"

class DoubleValue : public ValueBase
{
    Q_OBJECT
public:
    explicit DoubleValue(ValueGroup *valueGroup, QString id, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

signals:

public slots:
};

#endif // DOUBLEVALUE_H
