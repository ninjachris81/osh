#include "enumvalue.h"

EnumValue::EnumValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit, QObject *parent) : IntegerValue(valueGroup, id, valueType, alwaysEmit, parent)
{

}

QVariant EnumValue::_updateValue(QVariant newValue) {
    return IntegerValue::_updateValue(newValue);
}
