#ifndef ENUMVALUE_H
#define ENUMVALUE_H

#include <QObject>
#include "integervalue.h"

class EnumValue : public IntegerValue
{
    Q_OBJECT
public:
    explicit EnumValue(ValueGroup *valueGroup, QString id, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // ENUMVALUE_H
