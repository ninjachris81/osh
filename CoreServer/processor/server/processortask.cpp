#include "processortask.h"

#include <QDebug>
#include <QDateTime>

ProcessorTask::ProcessorTask(QString id, QString scriptCode, qint64 scheduleInterval, QObject *parent) : Identifyable(id, parent), m_scriptCode(scriptCode), m_scheduleInterval(scheduleInterval)
{

}

void ProcessorTask::run(QJSEngine *engine) {
    qDebug() << Q_FUNC_INFO << m_id;

    QJSValue result = engine->evaluate(m_scriptCode);

    if (!result.isError()) {
        qDebug() << "Result" << result.toVariant();
    } else {
        qWarning() << "Script execution error" << result.errorType();
    }

    m_lastExecution = QDateTime::currentMSecsSinceEpoch();
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
