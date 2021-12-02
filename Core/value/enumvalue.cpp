#include "enumvalue.h"

EnumValue::EnumValue(ValueGroup *valueGroup, QString id, UNIT_TYPE unitType, QObject *parent) : IntegerValue(valueGroup, id, unitType, parent)
{

}

QVariant EnumValue::_updateValue(QVariant newValue) {
    return IntegerValue::_updateValue(newValue);
}
