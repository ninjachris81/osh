#include "enumvalue.h"

EnumValue::EnumValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent) : IntegerValue(valueGroup, id, valueType, parent)
{

}

QVariant EnumValue::_updateValue(QVariant newValue) {
    return IntegerValue::_updateValue(newValue);
}
