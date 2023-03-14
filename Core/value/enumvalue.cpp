#include "enumvalue.h"

QLatin1String EnumValue::PROPERTY_ENUM_COUNT = QLatin1String("enumCount");

EnumValue::EnumValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, int enumCount, bool alwaysEmit, QObject *parent) : IntegerValue(valueGroup, id, valueType, alwaysEmit, parent), m_enumCount(enumCount)
{

}

QVariant EnumValue::_updateValue(QVariant newValue) {
    if (newValue.canConvert(QVariant::Int)) {
        int v = newValue.toInt();
        if (v < m_enumCount) {
            return IntegerValue::_updateValue(newValue);
        } else {
            iWarning() << "Invalid enum value" << newValue << m_enumCount;
        }
    }
    return QVariant();
}
