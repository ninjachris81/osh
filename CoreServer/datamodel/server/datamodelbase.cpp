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

QMap<QString, KnownRoom*> DatamodelBase::knownRooms() {
    return m_knownRooms;
}

KnownDevice* DatamodelBase::addKnownDevice(QString id, QString serviceId, QString name) {
    KnownDevice* device = new KnownDevice(id, serviceId, name);
    m_knownDevices.insert(device->fullId(), device);
    Q_EMIT(datamodelContentChanged());
    return device;
}

ValueGroup* DatamodelBase::addValueGroup(QString id) {
    ValueGroup* valueGroup = new ValueGroup(id);
    m_valueGroups.insert(valueGroup->id(), valueGroup);
    Q_EMIT(datamodelContentChanged());
    return valueGroup;
}

DigitalActor* DatamodelBase::addDigitalActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, bool isAsync, ValueBase::VALUE_TIMEOUT timeout) {
    DigitalActor* actor = new DigitalActor(valueGroup, id, valueType, isAsync);
    actor->withValueTimeout(timeout);
    m_actors.insert(actor->fullId(), actor);
    Q_EMIT(datamodelContentChanged());
    return actor;
}

BooleanValue* DatamodelBase::addBooleanValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout) {
    BooleanValue* value = new BooleanValue(valueGroup, id, valueType);
    value->withValueTimeout(timeout);
    m_values.insert(value->fullId(), value);
    Q_EMIT(datamodelContentChanged());
    return value;
}

IntegerValue* DatamodelBase::addIntegerValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout) {
    IntegerValue* value = new IntegerValue(valueGroup, id, valueType);
    value->withValueTimeout(timeout);
    m_values.insert(value->fullId(), value);
    Q_EMIT(datamodelContentChanged());
    return value;
}

DoubleValue* DatamodelBase::addDoubleValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout) {
    DoubleValue* value = new DoubleValue(valueGroup, id, valueType);
    value->withValueTimeout(timeout);
    m_values.insert(value->fullId(), value);
    Q_EMIT(datamodelContentChanged());
    return value;
}

ProcessorTask* DatamodelBase::addProcessorTask(QString id, ProcessorTask::ProcessorTaskType taskType, QString scriptCode, QString runCondition, qint64 scheduleInterval) {
    ProcessorTask* processorNode = new ProcessorTask(id, taskType, scriptCode, runCondition, scheduleInterval);
    m_processorTasks.insert(processorNode->id(), processorNode);
    Q_EMIT(datamodelContentChanged());
    return processorNode;
}

KnownRoom* DatamodelBase::addKnownRoom(QString id, QString name) {
    KnownRoom* knownRoom = new KnownRoom(id);
    knownRoom->setName(name);
    m_knownRooms.insert(knownRoom->id(), knownRoom);
    Q_EMIT(datamodelContentChanged());
    return knownRoom;
}
