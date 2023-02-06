#include "jsprocessortask.h"

#include <QDebug>
#include <QDateTime>
#include "processor/server/threadsafeqjsengine.h"


JSProcessorTask::JSProcessorTask() : ProcessorTaskBase() {

}

JSProcessorTask::JSProcessorTask(QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult, QObject *parent) : ProcessorTaskBase(id, taskType, taskTriggerType, scriptCode, runCondition, scheduleInterval, publishResult, parent)
{

}

void JSProcessorTask::serialize(QJsonObject &obj) {
    ProcessorTaskBase::serialize(obj);
}

void JSProcessorTask::deserialize(QJsonObject obj) {
    ProcessorTaskBase::deserialize(obj);
}

QString JSProcessorTask::getClassName() {
    return staticMetaObject.className();
}

QVariant JSProcessorTask::run() {
    iDebug() << Q_FUNC_INFO << m_id;

    if (m_engine == nullptr) {
        iWarning() << "No engine";
        return false;
    }

    if (checkRunCondition(m_engine)) {
        QJSValue result;

        result = ThreadSafeQJSEngine::call(m_engine, [&]{ return m_engine->evaluate(m_scriptCode);});

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

void JSProcessorTask::setEngine(QJSEngine* engine) {
    m_engine = engine;
}

bool JSProcessorTask::checkRunCondition(QJSEngine *engine) {
    if (m_runCondition.length() == 0) return true;
    return ThreadSafeQJSEngine::call(engine, [&]{ return engine->evaluate(m_runCondition);}).toBool();
}




