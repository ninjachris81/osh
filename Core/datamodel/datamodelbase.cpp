#include "datamodelbase.h"

DatamodelBase::DatamodelBase(QObject *parent) : QObject(parent)
{

}

QList<ValueBase*> DatamodelBase::values() {
    return m_values;
}
