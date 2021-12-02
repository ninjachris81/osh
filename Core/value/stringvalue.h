#ifndef STRINGVALUE_H
#define STRINGVALUE_H

#include <QObject>
#include "valuebase.h"

class StringValue : public ValueBase
{
    Q_OBJECT
public:
    explicit StringValue(ValueGroup *valueGroup, QString id, UNIT_TYPE unitType = UT_UNKNOWN, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // STRINGVALUE_H
