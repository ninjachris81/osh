#include "longvalue.h"

LongValue::LongValue(ValueGroup* valueGroup, QString id, UNIT_TYPE unitType, QObject *parent) : ValueBase(valueGroup, id, unitType, parent)
{

}

QVariant LongValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::LongLong)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
