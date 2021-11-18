#include "processortask.h"

#include <QDebug>
#include <QDateTime>

ProcessorTask::ProcessorTask(QString id, QString scriptCode, qint64 scheduleInterval, QObject *parent) : Identifyable(id, parent), m_scriptCode(scriptCode), m_scheduleInterval(scheduleInterval)
{

}

LogCat::LOGCAT ProcessorTask::logCat() {
    return LogCat::PROCESSOR;
}

void ProcessorTask::run(QJSEngine *engine) {
    iDebug() << Q_FUNC_INFO << m_id;

    QJSValue result = engine->evaluate(m_scriptCode);

    if (!result.isError()) {
        iDebug() << "Result" << result.toVariant();
        m_lastResult = result.toVariant();
    } else {
        iWarning() << "Script execution error" << result.errorType();
        m_lastResult = QVariant();
    }
    Q_EMIT(lastResultChanged());

    m_lastExecution = QDateTime::currentMSecsSinceEpoch();
    Q_EMIT(lastExecutionChanged());
}

QString ProcessorTask::scriptCode() {
    return m_scriptCode;
}

qint64 ProcessorTask::scheduleInterval() {
    return m_scheduleInterval;
}

qint64 ProcessorTask::lastExecution() {
    return m_lastExecution;
}

QVariant ProcessorTask::lastResult() {
    return m_lastResult;
}
