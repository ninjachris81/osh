#include "processortask.h"

#include <QDebug>
#include <QDateTime>

qint64 ProcessorTask::INTERVAL_REALTIME = 0;

ProcessorTask::ProcessorTask() : SerializableIdentifyable() {

}

ProcessorTask::ProcessorTask(QString id, ProcessorTaskType taskType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult, QObject *parent) : QObject(parent), SerializableIdentifyable(id), m_processorTaskType(taskType), m_scriptCode(scriptCode), m_runCondition(runCondition), m_scheduleInterval(scheduleInterval), m_publishResult(publishResult)
{

}

void ProcessorTask::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);
    obj.insert("scriptCode", m_scriptCode);
    obj.insert("runCondition", m_runCondition);
    obj.insert("scheduleInterval", m_scheduleInterval);
    obj.insert("processorTaskType", m_processorTaskType);
}

void ProcessorTask::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);
    m_scriptCode = obj.value("scriptCode").toString();
    m_runCondition = obj.value("runCondition").toString();
    m_scheduleInterval = obj.value("scheduleInterval").toVariant().toLongLong();
    m_processorTaskType = (ProcessorTaskType) obj.value("m_processorTaskType").toInt();
}

QString ProcessorTask::getClassName() {
    return staticMetaObject.className();
}

LogCat::LOGCAT ProcessorTask::logCat() {
    return LogCat::PROCESSOR;
}

QVariant ProcessorTask::run(QJSEngine *engine) {
    iDebug() << Q_FUNC_INFO << m_id;

    if (checkRunCondition(engine)) {
        QJSValue result = engine->evaluate(m_scriptCode);

        if (!result.isError()) {
            iDebug() << "Result" << result.toVariant();
            m_lastResult = result.toVariant();
        } else {
            iWarning() << "Script execution error" << result.errorType() << result.property("message").toString() << "Line" << result.property("lineNumber").toInt();
            m_lastResult = QVariant();
        }
        Q_EMIT(lastResultChanged());

        setLastExecutionNow();

        return m_lastResult;
    } else {
        iDebug() << "Run condition negative";
        return false;
    }
}

bool ProcessorTask::checkRunCondition(QJSEngine *engine) {
    if (m_runCondition.length() == 0) return true;
    return engine->evaluate(m_runCondition).toBool();
}

QString ProcessorTask::scriptCode() {
    return m_scriptCode;
}

qint64 ProcessorTask::scheduleInterval() {
    return m_scheduleInterval;
}

ProcessorTask::ProcessorTaskType ProcessorTask::taskType() {
    return m_processorTaskType;
}

bool ProcessorTask::publishResult() {
    return m_publishResult;
}

qint64 ProcessorTask::lastExecution() {
    return m_lastExecution;
}

QVariant ProcessorTask::lastResult() {
    return m_lastResult;
}

void ProcessorTask::setLastResult(QVariant lastResult) {
    m_lastResult = lastResult;
    Q_EMIT(lastResultChanged());
}

void ProcessorTask::setLastExecutionNow() {
    m_lastExecution = QDateTime::currentMSecsSinceEpoch();
    Q_EMIT(lastExecutionChanged());
}
