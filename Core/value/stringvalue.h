#ifndef STRINGVALUE_H
#define STRINGVALUE_H

#include <QObject>

#include "sharedlib.h"

#include "valuebase.h"

class SHARED_LIB_EXPORT StringValue : public ValueBase
{
    Q_OBJECT
public:
    explicit StringValue();
    explicit StringValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit = true, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;

signals:

public slots:
};

#endif // STRINGVALUE_H
