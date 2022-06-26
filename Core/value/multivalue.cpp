#include "multivalue.h"

MultiValue::MultiValue() : ValueBase()
{

}

MultiValue::MultiValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent) : ValueBase (valueGroup, id, valueType, UT_UNKNOWN, parent)
{

}

QVariant MultiValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Map)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
