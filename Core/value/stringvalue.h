#ifndef STRINGVALUE_H
#define STRINGVALUE_H

#include <QObject>
#include "valuebase.h"

class StringValue : public ValueBase
{
    Q_OBJECT
public:
    explicit StringValue(ValueGroup *valueGroup, QString id, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

signals:

public slots:
};

#endif // STRINGVALUE_H
