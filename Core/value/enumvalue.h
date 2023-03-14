#ifndef ENUMVALUE_H
#define ENUMVALUE_H

#include <QObject>

#include "sharedlib.h"

#include "integervalue.h"

class SHARED_LIB_EXPORT EnumValue : public IntegerValue
{
    Q_OBJECT
public:

    static QLatin1String PROPERTY_ENUM_COUNT;

    explicit EnumValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, int enumCount, bool alwaysEmit = true, QObject *parent = nullptr);

    /*virtual*/ QVariant _updateValue(QVariant newValue) override;


private:
    int m_enumCount = 0;

signals:

public slots:
};

#endif // ENUMVALUE_H
