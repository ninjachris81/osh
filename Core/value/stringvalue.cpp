#include "stringvalue.h"

StringValue::StringValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent) : ValueBase(valueGroup, id, valueType, parent)
{

}

QVariant StringValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::String)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
