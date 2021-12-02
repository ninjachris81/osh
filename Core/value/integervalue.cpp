#include "integervalue.h"

IntegerValue::IntegerValue(ValueGroup *valueGroup, QString id, UNIT_TYPE unitType, QObject *parent) : ValueBase(valueGroup, id, unitType, parent)
{

}

QVariant IntegerValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Int)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
