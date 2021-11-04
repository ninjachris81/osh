#include "booleanvalue.h"

BooleanValue::BooleanValue(ValueGroup *valueGroup, QString id, QObject *parent) : ValueBase (valueGroup, id, parent)
{

}

QVariant BooleanValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Bool)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
