#include "longvalue.h"

LongValue::LongValue() : ValueBase() {
}

LongValue::LongValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit, QObject *parent) : ValueBase(valueGroup, id, valueType, alwaysEmit, parent)
{

}

QVariant LongValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::LongLong)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
