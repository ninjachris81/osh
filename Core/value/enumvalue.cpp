#include "enumvalue.h"

EnumValue::EnumValue(ValueGroup *valueGroup, QString id, QObject *parent) : IntegerValue(valueGroup, id, parent)
{

}

QVariant EnumValue::_updateValue(QVariant newValue) {
    return IntegerValue::_updateValue(newValue);
}
