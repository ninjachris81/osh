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

QMap<QString, ActorBase*> DatamodelBase::actors() {
    return m_actors;
}

KnownDevice* DatamodelBase::addKnownDevice(QString id, QString serviceId, QString name) {
    KnownDevice* device = new KnownDevice(id, serviceId, name);
    m_knownDevices.insert(device->fullId(), device);
    return device;
}

ValueGroup* DatamodelBase::addValueGroup(QString id) {
    return new ValueGroup(id);
}

DigitalActor* DatamodelBase::addDigitalActor(ValueGroup* valueGroup, QString id, bool isAsync, ValueBase::VALUE_TIMEOUT timeout) {
    DigitalActor* actor = new DigitalActor(valueGroup, id, isAsync);
    actor->withValueTimeout(timeout);
    m_actors.insert(actor->fullId(), actor);
    return actor;
}

BooleanValue* DatamodelBase::addBooleanValue(ValueGroup* valueGroup, QString id, ValueBase::VALUE_TIMEOUT timeout) {
    BooleanValue* value = new BooleanValue(valueGroup, id);
    value->withValueTimeout(timeout);
    m_values.insert(value->fullId(), value);
    return value;
}

DoubleValue* DatamodelBase::addDoubleValue(ValueGroup* valueGroup, QString id, UNIT_TYPE unitType, ValueBase::VALUE_TIMEOUT timeout) {
    DoubleValue* value = new DoubleValue(valueGroup, id, unitType);
    value->withValueTimeout(timeout);
    m_values.insert(value->fullId(), value);
    return value;
}

ProcessorTask* DatamodelBase::addProcessorTask(QString id, QString scriptCode, qint64 scheduleInterval) {
    ProcessorTask* processorNode = new ProcessorTask(id, scriptCode, scheduleInterval);
    m_processorTasks.insert(processorNode->id(), processorNode);
    return processorNode;
}

