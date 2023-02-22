#include "processortaskbase.h"
#include <QDateTime>

qint64 ProcessorTaskBase::INTERVAL_REALTIME = 0;

QLatin1String ProcessorTaskBase::PROPERTY_TASK_TYPE = QLatin1String("taskType");
QLatin1String ProcessorTaskBase::PROPERTY_TASK_TRIGGER_TYPE = QLatin1String("taskTriggerType");
QLatin1String ProcessorTaskBase::PROPERTY_SCRIPT_CODE = QLatin1String("scriptCode");
QLatin1String ProcessorTaskBase::PROPERTY_RUN_CONDITION = QLatin1String("runCondition");
QLatin1String ProcessorTaskBase::PROPERTY_SCHEDULE_INTERVAL =QLatin1String("scheduleInterval");
QLatin1String ProcessorTaskBase::PROPERTY_PUBLISH_RESULT = QLatin1String("publishResult");

ProcessorTaskBase::ProcessorTaskBase() : QObject() {
}

ProcessorTaskBase::ProcessorTaskBase(QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult, QObject *parent)
    : QObject{parent}, SerializableIdentifyable(id), m_processorTaskType(taskType), m_processorTaskTriggerType(taskTriggerType), m_scriptCode(scriptCode), m_runCondition(runCondition), m_scheduleInterval(scheduleInterval), m_publishResult(publishResult)
{

}

void ProcessorTaskBase::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);
    obj.insert("scriptCode", m_scriptCode);
    obj.insert("runCondition", m_runCondition);
    obj.insert("scheduleInterval", m_scheduleInterval);
    obj.insert("processorTaskType", m_processorTaskTriggerType);
}

void ProcessorTaskBase::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);
    m_scriptCode = obj.value("scriptCode").toString();
    m_runCondition = obj.value("runCondition").toString();
    m_scheduleInterval = obj.value("scheduleInterval").toVariant().toLongLong();
    m_processorTaskTriggerType = (ProcessorTaskTriggerType) obj.value("m_processorTaskType").toInt();
}

LogCat::LOGCAT ProcessorTaskBase::logCat() {
    return LogCat::PROCESSOR;
}

QString ProcessorTaskBase::scriptCode() {
    return m_scriptCode;
}

qint64 ProcessorTaskBase::scheduleInterval() {
    return m_scheduleInterval;
}
ProcessorTaskBase::ProcessorTaskType ProcessorTaskBase::taskType() {
    return m_processorTaskType;
}

ProcessorTaskBase::ProcessorTaskTriggerType ProcessorTaskBase::taskTriggerType() {
    return m_processorTaskTriggerType;
}

bool ProcessorTaskBase::publishResult() {
    return m_publishResult;
}

qint64 ProcessorTaskBase::lastExecution() {
    return m_lastExecution;
}

QVariant ProcessorTaskBase::lastResult() {
    return m_lastResult;
}

void ProcessorTaskBase::setLastResult(QVariant lastResult) {
    m_lastResult = lastResult;
    Q_EMIT(lastResultChanged());
}

void ProcessorTaskBase::setLastExecutionNow() {
    m_lastExecution = QDateTime::currentMSecsSinceEpoch();
    Q_EMIT(lastExecutionChanged());
}
