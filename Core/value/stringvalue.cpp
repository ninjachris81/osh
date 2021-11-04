#include "stringvalue.h"

StringValue::StringValue(ValueGroup *valueGroup, QString id, QObject *parent) : ValueBase(valueGroup, id, parent)
{

}

QVariant StringValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::String)) {
        return QVariant::fromValue(newValue);
    } else {
        return QVariant();
    }
}
