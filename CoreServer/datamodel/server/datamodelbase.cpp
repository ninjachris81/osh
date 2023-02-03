#include "datamodelbase.h"

DatamodelBase::DatamodelBase(QString id, QObject *parent) : Identifyable (id), QObject(parent)
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

ShutterActor* DatamodelBase::addShutterActor(ValueGroup* valueGroupState, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout) {
    ShutterActor* actor = new ShutterActor(valueGroupState, id, valueType);
    actor->withValueTimeout(timeout);
    m_actors.insert(actor->fullId(), actor);
    Q_EMIT(datamodelContentChanged());
    return actor;
}

ShutterActor* DatamodelBase::addShutterActor(ValueGroup* valueGroupState, ValueGroup* valueGroupCloseState, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout) {
    ShutterActor* actor = addShutterActor(valueGroupState, id, valueType, timeout);
    IntegerValue *closeState = addIntegerValue(valueGroupCloseState, id, VALUE_TYPE::VALTYPE_SHUTTER_CLOSE_STATE, ValueBase::VALUE_TIMEOUT::VT_MID);
    actor->setCloseState(closeState);
    return actor;
}

ShutterActor* DatamodelBase::addShutterActor(ValueGroup* valueGroupState, ValueGroup* valueGroupCloseState, ValueGroup* valueGroupTiltState, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout) {
    ShutterActor* actor = addShutterActor(valueGroupState, valueGroupCloseState, id, valueType, timeout);
    IntegerValue *tiltState = addIntegerValue(valueGroupTiltState, id, VALUE_TYPE::VALTYPE_SHUTTER_TILT_STATE, ValueBase::VALUE_TIMEOUT::VT_MID);
    actor->setTiltState(tiltState);
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

ProcessorTask* DatamodelBase::addProcessorTask(QString id, ProcessorTask::ProcessorTaskType taskType, ProcessorTask::ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult) {
    ProcessorTask* processorNode = new ProcessorTask(id, taskType, taskTriggerType, scriptCode, runCondition, scheduleInterval, publishResult);

    if (taskType == ProcessorTask::PTT_NATIVE) {
        parseNativeFunction(scriptCode, processorNode);
    }

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

void DatamodelBase::parseNativeFunction(QString scriptCode, ProcessorTask *task) {
    iDebug() << Q_FUNC_INFO << scriptCode;

    if (scriptCode.startsWith("CommonScripts.applySwitchLogic(") && scriptCode.endsWith(")")) {
        task->setNativeFunction(ProcessorTask::NFT_APPLY_SWITCH_LOGIC);
        extractParams(scriptCode, task);
    } else {
        iWarning() << "Unable to resolve native function" << scriptCode;
    }
}

void DatamodelBase::extractParams(QString scriptCode, ProcessorTask *task) {
    iDebug() << Q_FUNC_INFO << scriptCode;

    int start = scriptCode.indexOf("(");
    int end = scriptCode.lastIndexOf(")");

    QString params = scriptCode.mid(start + 1, end - (start + 1));
    QStringList paramTokens = params.split(",");
    QList<QVariant::Type> typeList = ProcessorTask::paramTypeList(task->nativeFunction());

    for (quint8 i = 0; i < paramTokens.size();i++) {
        QString str = paramTokens.at(i).trimmed();
        if (str.startsWith("'")) str = str.mid(1);
        if (str.endsWith("'")) str = str.chopped(1);

        QVariant var = QVariant::fromValue(str);
        var.convert(typeList.at(i));
        task->addNativeParam(var);
    }
}
