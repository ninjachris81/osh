#include "processortask.h"

#include <QDebug>
#include <QDateTime>

ProcessorTask::ProcessorTask(QString id, ProcessorTaskType taskType, QString scriptCode, qint64 scheduleInterval, QObject *parent) : Identifyable(id, parent), m_processorTaskType(taskType), m_scriptCode(scriptCode), m_scheduleInterval(scheduleInterval)
{

}

LogCat::LOGCAT ProcessorTask::logCat() {
    return LogCat::PROCESSOR;
}

QVariant ProcessorTask::run(QJSEngine *engine) {
    iDebug() << Q_FUNC_INFO << m_id;

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
