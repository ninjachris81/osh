#include "processortask.h"

#include <QDebug>
#include <QDateTime>
#include "processor/server/threadsafeqjsengine.h"
#include "processor/server/commonscripts.h"

qint64 ProcessorTask::INTERVAL_REALTIME = 0;

ProcessorTask::ProcessorTask() : SerializableIdentifyable() {

}

ProcessorTask::ProcessorTask(QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult, QObject *parent) : QObject(parent), SerializableIdentifyable(id), m_scriptCode(scriptCode), m_runCondition(runCondition), m_scheduleInterval(scheduleInterval), m_publishResult(publishResult), m_processorTaskType(taskType), m_processorTaskTriggerType(taskTriggerType)
{

}

void ProcessorTask::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);
    obj.insert("scriptCode", m_scriptCode);
    obj.insert("runCondition", m_runCondition);
    obj.insert("scheduleInterval", m_scheduleInterval);
    obj.insert("processorTaskType", m_processorTaskTriggerType);
}

void ProcessorTask::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);
    m_scriptCode = obj.value("scriptCode").toString();
    m_runCondition = obj.value("runCondition").toString();
    m_scheduleInterval = obj.value("scheduleInterval").toVariant().toLongLong();
    m_processorTaskTriggerType = (ProcessorTaskTriggerType) obj.value("m_processorTaskType").toInt();
}

QString ProcessorTask::getClassName() {
    return staticMetaObject.className();
}

LogCat::LOGCAT ProcessorTask::logCat() {
    return LogCat::PROCESSOR;
}

QVariant ProcessorTask::run(QJSEngine *engine, CommonScripts *commonScripts) {
    iDebug() << Q_FUNC_INFO << m_id;

    if (checkRunCondition(engine)) {
        QJSValue result;

        switch(m_processorTaskType) {
        case PTT_JS:
            result = ThreadSafeQJSEngine::call(engine, [&]{ return engine->evaluate(m_scriptCode);});

            if (!result.isError()) {
                iDebug() << "Result" << result.toVariant();
                m_lastResult = result.toVariant();
            } else {
                iWarning() << "Script execution error" << result.errorType() << result.property("message").toString() << "Line" << result.property("lineNumber").toInt();
                m_lastResult = QVariant();
            }
            break;
        case PTT_NATIVE:
            switch(m_nativeFunction) {
            case NFT_APPLY_SWITCH_LOGIC:
                commonScripts->applySwitchLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toInt());
                break;
            default:
                break;
            }
            break;
        default:
            break;
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
    return ThreadSafeQJSEngine::call(engine, [&]{ return engine->evaluate(m_runCondition);}).toBool();
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

ProcessorTask::ProcessorTaskTriggerType ProcessorTask::taskTriggerType() {
    return m_processorTaskTriggerType;
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

void ProcessorTask::setNativeFunction(ProcessorTask::NativeFunctionType nativeFunction) {
    m_nativeFunction = nativeFunction;
}

ProcessorTask::NativeFunctionType ProcessorTask::nativeFunction() {
    return m_nativeFunction;
}

void ProcessorTask::addNativeParam(QVariant value) {
    iDebug() << Q_FUNC_INFO << value;

    m_nativeParams.append(value);
}

QVariantList ProcessorTask::nativeParams() {
    return m_nativeParams;
}

QList<QVariant::Type> ProcessorTask::paramTypeList(ProcessorTask::NativeFunctionType nativeFunction) {
    switch(nativeFunction) {
    case ProcessorTask::NFT_APPLY_SWITCH_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::Int;
    default:
        return QList<QVariant::Type>();
    }
}

