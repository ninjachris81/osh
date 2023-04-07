#include "stringvalue.h"

StringValue::StringValue() : ValueBase() {
}

StringValue::StringValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit, QObject *parent) : ValueBase(valueGroup, id, valueType, alwaysEmit, QVariant::String, parent)
{

}

QVariant StringValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::String)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
