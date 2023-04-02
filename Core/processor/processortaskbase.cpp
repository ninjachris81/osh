#include "processortaskbase.h"
#include <QDateTime>

qint64 ProcessorTaskBase::INTERVAL_REALTIME = 0;

QLatin1String ProcessorTaskBase::PROPERTY_GROUP_ID = QLatin1String("group_id");
QLatin1String ProcessorTaskBase::PROPERTY_TASK_TYPE = QLatin1String("task_type");
QLatin1String ProcessorTaskBase::PROPERTY_TASK_TRIGGER_TYPE = QLatin1String("task_trigger_type");
//QLatin1String ProcessorTaskBase::PROPERTY_RUN_CONDITION = QLatin1String("run_condition");
QLatin1String ProcessorTaskBase::PROPERTY_SCHEDULE_INTERVAL =QLatin1String("schedule_interval");
//QLatin1String ProcessorTaskBase::PROPERTY_PUBLISH_RESULT = QLatin1String("publish_result");
QLatin1String ProcessorTaskBase::PROPERTY_ENABLED = QLatin1String("enabled");
QLatin1String ProcessorTaskBase::PROPERTY_FUNCTION_CODE = QLatin1String("function_code");
QLatin1String ProcessorTaskBase::PROPERTY_PARAM_PREFIX = QLatin1String("param_");

ProcessorTaskBase::ProcessorTaskBase() : QObject() {
}

ProcessorTaskBase::ProcessorTaskBase(QString groupId, QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, int functionCode, QStringList params, qint64 scheduleInterval, bool enabled, QObject *parent)
    : QObject{parent}, SerializableIdentifyable(id), m_processorTaskType(taskType), m_processorTaskTriggerType(taskTriggerType), m_functionCode(functionCode), m_paramList(params), m_scheduleInterval(scheduleInterval), m_enabled(enabled), m_groupId(groupId)
{

}

void ProcessorTaskBase::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);
}

void ProcessorTaskBase::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);
}

LogCat::LOGCAT ProcessorTaskBase::logCat() {
    return LogCat::PROCESSOR;
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

/*
bool ProcessorTaskBase::publishResult() {
    return m_publishResult;
}
*/

bool ProcessorTaskBase::isEnabled() {
    return m_enabled;
}

qint64 ProcessorTaskBase::lastExecution() {
    return m_lastExecution;
}

QVariant ProcessorTaskBase::lastResult() {
    return m_lastResult;
}

QString ProcessorTaskBase::groupId() {
    return m_groupId;
}

int ProcessorTaskBase::functionCode() {
    return m_functionCode;
}

QStringList ProcessorTaskBase::paramList() {
    return m_paramList;
}


void ProcessorTaskBase::setLastResult(QVariant lastResult) {
    m_lastResult = lastResult;
    Q_EMIT(lastResultChanged());
}

void ProcessorTaskBase::setLastExecutionNow() {
    m_lastExecution = QDateTime::currentMSecsSinceEpoch();
    Q_EMIT(lastExecutionChanged());
}

void ProcessorTaskBase::setEnabled(bool enabled) {
    m_enabled = enabled;
}
