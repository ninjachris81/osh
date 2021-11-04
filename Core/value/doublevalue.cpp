#include "doublevalue.h"

DoubleValue::DoubleValue(ValueGroup *valueGroup, QString id, QObject *parent) : ValueBase(valueGroup, id, parent)
{

}

QVariant DoubleValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Double)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
