#include "integervalue.h"

IntegerValue::IntegerValue() : ValueBase() {
}

IntegerValue::IntegerValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit, QObject *parent) : ValueBase(valueGroup, id, valueType, alwaysEmit, QVariant::Int, parent)
{

}

QVariant IntegerValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Int)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
