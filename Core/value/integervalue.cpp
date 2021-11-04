#include "integervalue.h"

IntegerValue::IntegerValue(ValueGroup *valueGroup, QString id, QObject *parent) : ValueBase(valueGroup, id, parent)
{

}

QVariant IntegerValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Int)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
