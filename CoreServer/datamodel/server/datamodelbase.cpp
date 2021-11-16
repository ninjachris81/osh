#include "datamodelbase.h"

DatamodelBase::DatamodelBase(QString id, QObject *parent) : Identifyable (id, parent)
{

}

LogCat::LOGCAT DatamodelBase::logCat() {
    return LogCat::DATAMODEL;
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
