#include "datamodelbase.h"

DatamodelBase::DatamodelBase(QString id, QObject *parent) : QObject(parent), Identifyable (id)
{

}

void DatamodelBase::setProcessorTaskFactory(ProcessorTaskFactory* processorTaskFactory) {
    m_processorTaskFactory = processorTaskFactory;
}

LogCat::LOGCAT DatamodelBase::logCat() {
    return LogCat::DATAMODEL;
}

QList<ValueGroup*> DatamodelBase::valueGroups() {
    return m_valueGroups.values();
}

ValueGroup* DatamodelBase::valueGroup(QString id) {
    return m_valueGroups.value(id);
}

QMap<QString, ValueBase*> DatamodelBase::values() {
    return m_values;
}

QMap<QString, KnownDevice*> DatamodelBase::knownDevices() {
    return m_knownDevices;
}

QMap<QString, ProcessorTaskBase *> DatamodelBase::processorTasks() {
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

DigitalActor* DatamodelBase::addDigitalActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, bool isAsync) {
    DigitalActor* actor = new DigitalActor(valueGroup, id, valueType, isAsync);
    actor->withValueTimeout(timeout);
    m_actors.insert(actor->fullId(), actor);
    Q_EMIT(datamodelContentChanged());
    return actor;
}

ShutterActor* DatamodelBase::addShutterActor(ValueGroup* valueGroupState, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, bool tiltSupport, int fullCloseDuration) {
    ShutterActor* actor = new ShutterActor(valueGroupState, id, valueType);
    actor->withValueTimeout(timeout);
    QVariantMap config;
    config.insert(ShutterActor::CONFIG_TILT_SUPPORT, tiltSupport);
    config.insert(ShutterActor::CONFIG_FULL_CLOSE_DURATION, fullCloseDuration);
    actor->setConfig(config);
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

LongValue* DatamodelBase::addLongValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout) {
    LongValue* value = new LongValue(valueGroup, id, valueType);
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

StringValue* DatamodelBase::addStringValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout) {
    StringValue* value = new StringValue(valueGroup, id, valueType);
    value->withValueTimeout(timeout);
    m_values.insert(value->fullId(), value);
    Q_EMIT(datamodelContentChanged());
    return value;
}

ProcessorTaskBase* DatamodelBase::addProcessorTask(QString id, ProcessorTaskBase::ProcessorTaskType taskType, ProcessorTaskBase::ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult) {
    if (m_processorTaskFactory != nullptr) {
        ProcessorTaskBase* processorNode = m_processorTaskFactory->createProcessorTask(id, taskType, taskTriggerType, scriptCode, runCondition, scheduleInterval, publishResult);
        if (processorNode != nullptr) {
            m_processorTasks.insert(processorNode->id(), processorNode);
            Q_EMIT(datamodelContentChanged());
            return processorNode;
        } else {
            iWarning() << "Failed to create processor node" << id;
        }
    } else {
        iWarning() << "No processor factory set!";
    }

    return nullptr;
}

KnownRoom* DatamodelBase::addKnownRoom(KnownArea* knownArea, QString id, QString name) {
    KnownRoom* knownRoom = new KnownRoom(id);
    knownRoom->setName(name);
    m_knownRooms.insert(knownRoom->id(), knownRoom);
    knownArea->addKnownRoom(knownRoom);
    Q_EMIT(datamodelContentChanged());
    return knownRoom;
}

KnownArea* DatamodelBase::addKnownArea(QString id, QString name) {
    KnownArea* knownArea = new KnownArea(id);
    knownArea->setName(name);
    m_knownAreas.insert(knownArea->id(), knownArea);
    Q_EMIT(datamodelContentChanged());
    return knownArea;
}

KnownArea *DatamodelBase::knownArea(QString id) {
    return m_knownAreas.value(id);
}