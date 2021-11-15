#include "longvalue.h"

LongValue::LongValue(ValueGroup* valueGroup, QString id, QObject *parent) : ValueBase(valueGroup, id, parent)
{

}

QVariant LongValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::LongLong)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
