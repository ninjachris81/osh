#include "redundantvalue.h"

RedundantValue::RedundantValue(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, bool alwaysEmit, QObject *parent) : ValueBase(valueGroup, id, valueType, alwaysEmit, QVariant::Invalid, parent)
{

}

QVariant RedundantValue::_updateValue(QVariant newValue) {
    // TBD: disallow or update all?
    qDebug() << "TODO";
    return QVariant();
}

void RedundantValue::addNextValue(ValueBase* value) {
    if (!m_values.contains(value)) {

        // check other types
        QListIterator<ValueBase*> it(m_values);
        while(it.hasNext()) {
            ValueBase* v = it.next();

            if (!value->inherits(v->metaObject()->className())) {
                iWarning() << "Already added value has different type" << v->metaObject()->className() << value->metaObject()->className();
            }
        }

        m_values.append(value);
    } else {
        iWarning() << "Value already added";
    }
}
