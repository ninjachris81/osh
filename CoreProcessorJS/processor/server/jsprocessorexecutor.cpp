#include "jsprocessorexecutor.h"

#include <QDebug>

JSProcessorExecutor::JSProcessorExecutor(DatamodelManager *dmManager, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager *actorManager, QObject *parent)
    : ProcessorExecutorBase("JSProcessorExecutor", dmManager, localStorage, valueManager, actorManager, parent)
{
    m_engine.installExtensions(QJSEngine::AllExtensions);

    m_jsMethods = new JSMethods(valueManager, actorManager);
    QJSValue val = m_engine.newQObject(m_jsMethods);
    m_engine.globalObject().setProperty("OSH", val);
}

QVariant JSProcessorExecutor::execute(JSProcessorTask* task) {
    task->setEngine(&m_engine);
    return task->run();
}

QVariant JSProcessorExecutor::execute(ProcessorTaskBase* task) {
    JSProcessorTask *nTask = qobject_cast<JSProcessorTask*>(task);
    if (nTask != nullptr) {
        return execute(nTask);
    } else {
        iWarning() << "Wrong task type";
        return false;
    }
}
