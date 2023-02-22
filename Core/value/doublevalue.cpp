#include "doublevalue.h"

DoubleValue::DoubleValue() : ValueBase() {
}

DoubleValue::DoubleValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit, QObject *parent) : ValueBase(valueGroup, id, valueType, alwaysEmit, parent)
{

}

QVariant DoubleValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Double)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
