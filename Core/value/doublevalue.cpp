#include "doublevalue.h"

DoubleValue::DoubleValue(ValueGroup *valueGroup, QString id, UNIT_TYPE unitType, QObject *parent) : ValueBase(valueGroup, id, unitType, parent)
{

}

QVariant DoubleValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Double)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
