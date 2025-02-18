#include "nativeprocessorexecutor.h"

NativeProcessorExecutor::NativeProcessorExecutor(DatamodelManager *dmManager, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager *actorManager, QObject *parent)
    : ProcessorExecutorBase("NativeProcessorExecutor", dmManager, localStorage, valueManager, actorManager, parent)
{
    m_basicScripts = new BasicScripts(dmManager->datamodel(), localStorage, valueManager, actorManager, this);
    m_commonScripts = new CommonScripts(dmManager->datamodel(), localStorage, valueManager, actorManager, this);
    m_advScripts = new AdvancedScripts(dmManager->datamodel(), localStorage, valueManager, actorManager, this);
}


QVariant NativeProcessorExecutor::execute(NativeProcessorTask* task) {
    task->setScripts(m_basicScripts, m_commonScripts, m_advScripts);
    return task->run();
}

QVariant NativeProcessorExecutor::execute(ProcessorTaskBase* task) {
    NativeProcessorTask *nTask = qobject_cast<NativeProcessorTask*>(task);
    if (nTask != nullptr) {
        return execute(nTask);
    } else {
        iWarning() << "Wrong task type";
        return false;
    }
}
