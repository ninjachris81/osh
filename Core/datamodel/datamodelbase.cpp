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

ValueBase* DatamodelBase::value(QString valueFullId) {
    return m_values.value(valueFullId);
}

QMap<QString, ValueBase*> DatamodelBase::values() {
    return m_values;
}

QMap<QString, ValueBase*> DatamodelBase::values(QString valueGroupId) {
    QMap<QString, ValueBase*> returnMap;

    QMapIterator<QString, ValueBase*> it(m_values);
    while (it.hasNext()) {
        it.next();

        if (it.value()->valueGroup()->id() == valueGroupId) {
            returnMap.insert(it.key(), it.value());
        }
    }

    return returnMap;
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

ActorBase* DatamodelBase::actor(QString actorFullId) {
    return m_actors.value(actorFullId);
}

QMap<QString, ActorBase*> DatamodelBase::actors(QString valueGroupId) {
    QMap<QString, ActorBase*> returnMap;

    QMapIterator<QString, ActorBase*> it(m_actors);
    while (it.hasNext()) {
        it.next();

        if (it.value()->valueGroup()->id() == valueGroupId) {
            returnMap.insert(it.key(), it.value());
        }
    }

    return returnMap;
}

QMap<QString, KnownRoom*> DatamodelBase::knownRooms() {
    return m_knownRooms;
}

QMap<QString, OshUser*> DatamodelBase::users() {
    return m_users;
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

ToggleActor* DatamodelBase::addToggleActor(ValueGroup* valueGroup, QString id) {
    ToggleActor* actor = new ToggleActor(valueGroup, id);
    m_actors.insert(actor->fullId(), actor);
    Q_EMIT(datamodelContentChanged());
    return actor;
}


DigitalActor* DatamodelBase::addDigitalActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, bool isAsync) {
    DigitalActor* actor = new DigitalActor(valueGroup, id, valueType, isAsync);
    actor->withValueTimeout(timeout);
    m_actors.insert(actor->fullId(), actor);
    Q_EMIT(datamodelContentChanged());
    return actor;
}

ShutterActor* DatamodelBase::addShutterActor(ValueGroup* valueGroupState, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, bool tiltSupport, int fullCloseDuration, int fullTiltDuration) {
    ShutterActor* actor = new ShutterActor(valueGroupState, id, valueType, tiltSupport, fullCloseDuration, fullTiltDuration);
    actor->withValueTimeout(timeout);
    m_actors.insert(actor->fullId(), actor);
    Q_EMIT(datamodelContentChanged());
    return actor;
}

ValueActor* DatamodelBase::addValueActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, QVariant::Type typeHint) {
    ValueActor* actor = new ValueActor(valueGroup, id, valueType, typeHint);
    actor->withValueTimeout(timeout);
    m_actors.insert(actor->fullId(), actor);
    Q_EMIT(datamodelContentChanged());
    return actor;
}

AudioPlaybackActor* DatamodelBase::addAudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, QString audioDeviceIds, QString audioActivationRelayId, float audioVolume, QString audioVolumeId, QString audioUrl, QString audioUrlId, QString audioCurrentTitleId, QString audioName) {
    AudioPlaybackActor* actor = new AudioPlaybackActor(valueGroup, id, valueType, audioDeviceIds, audioActivationRelayId, audioVolume, audioVolumeId, audioUrl, audioUrlId, audioCurrentTitleId, audioName);
    actor->withValueTimeout(timeout);
    m_actors.insert(actor->fullId(), actor);
    Q_EMIT(datamodelContentChanged());
    return actor;
}

DoorActor* DatamodelBase::addDoorActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout) {
    DoorActor* actor = new DoorActor(valueGroup, id, valueType);
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

EnumValue* DatamodelBase::addEnumValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, int enumCount) {
    EnumValue* value = new EnumValue(valueGroup, id, valueType, enumCount);
    value->withValueTimeout(timeout);
    m_values.insert(value->fullId(), value);
    Q_EMIT(datamodelContentChanged());
    return value;
}

ProcessorVariable* DatamodelBase::addProcessorVariable(QString id, QString value) {
    ProcessorVariable *var = new ProcessorVariable(id, value);
    m_processorVariables.insert(var->id(), var);
    Q_EMIT(datamodelContentChanged());
    return var;
}

/*
ProcessorTaskBase* DatamodelBase::addProcessorTask(QString groupId, QString id, ProcessorTaskBase::ProcessorTaskType taskType, ProcessorTaskBase::ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult, bool isEnabled) {
    if (m_processorTaskFactory != nullptr) {
        for (ProcessorVariable* var : m_processorVariables.values()) {
            var->replaceScriptCode(scriptCode);
        }

        ProcessorTaskBase* processorNode = m_processorTaskFactory->createProcessorTask(groupId, id, taskType, taskTriggerType, scriptCode, runCondition, scheduleInterval, publishResult);
        processorNode->setEnabled(isEnabled);
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
}*/

ProcessorTaskBase* DatamodelBase::addProcessorTask(QString groupId, QString id, ProcessorTaskBase::ProcessorTaskType taskType, ProcessorTaskBase::ProcessorTaskTriggerType taskTriggerType, int functionCode, QStringList params, qint64 scheduleInterval, bool isEnabled) {
    if (m_processorTaskFactory != nullptr) {
        QStringList resolvedParams;
        for (QString param : params) {
            for (ProcessorVariable* var : m_processorVariables.values()) {
                var->replaceScriptCode(param);
            }
            resolvedParams << param;
        }

        ProcessorTaskBase* processorNode = m_processorTaskFactory->createProcessorTask(groupId, id, taskType, taskTriggerType, functionCode, resolvedParams, scheduleInterval);
        processorNode->setEnabled(isEnabled);
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

OshUser* DatamodelBase::addUser(QString id, QString name, QStringList rights) {
    OshUser* user = new OshUser(id, name, rights);
    m_users.insert(user->id(), user);
    Q_EMIT(datamodelContentChanged());
    return user;
}
