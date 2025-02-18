#include "booleanvalue.h"

BooleanValue::BooleanValue() : ValueBase() {
}

BooleanValue::BooleanValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit, QObject *parent) : ValueBase (valueGroup, id, valueType, alwaysEmit, QVariant::Bool, parent)
{

}

QVariant BooleanValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Bool)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
