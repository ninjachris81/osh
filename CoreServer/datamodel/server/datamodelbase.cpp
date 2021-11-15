#include "datamodelbase.h"

DatamodelBase::DatamodelBase(QObject *parent) : QObject(parent)
{

}

QMap<QString, ValueBase*> DatamodelBase::values() {
    return m_values;
}

QMap<QString, KnownDevice*> DatamodelBase::knownDevices() {
    return m_knownDevices;
}

QMap<QString, ProcessorTask*> DatamodelBase::processorTasks() {
    return m_processorTasks;
}
