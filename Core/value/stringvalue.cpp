#include "stringvalue.h"

StringValue::StringValue(ValueGroup *valueGroup, QString id, UNIT_TYPE unitType, QObject *parent) : ValueBase(valueGroup, id, unitType, parent)
{

}

QVariant StringValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::String)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
