#include "modelprocessormanager.h"

#include <QDebug>
#include <QDateTime>
#include <QMetaEnum>
#include <QResource>
#include <QThread>

#include "actor/scripttriggeractor.h"
#include "helpers.h"
#include "macros.h"
#include "value/server/servervaluemanager.h"
#include "shared/actor_qt.h"
#include "processor/server/commonscripts.h"
#include "processor/scriptresultmessage.h"
#include "processor/server/nativeprocessorexecutor.h"
#include "processor/server/nativeprocessortask.h"

#ifdef PROCESSOR_JS_SUPPORT
    #include "processor/server/jsprocessorexecutor.h"
#endif

QLatin1String ModelProcessorManager::MANAGER_ID = QLatin1String("ModelProcessorManager");


ModelProcessorManager::ModelProcessorManager(QObject *parent) : ManagerBase(parent)
{
    connect(&m_scheduleTimer, &QTimer::timeout, this, &ModelProcessorManager::executeTasks);
}

ProcessorTaskBase* ModelProcessorManager::createProcessorTask(QString id, ProcessorTaskBase::ProcessorTaskType taskType, ProcessorTaskBase::ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult) {

    switch(taskType) {
        case ProcessorTaskBase::PTT_JS:
#ifdef PROCESSOR_JS_SUPPORT
            return new JSProcessorTask(id, taskType, taskTriggerType, scriptCode, runCondition, scheduleInterval, publishResult);
#else
            qWarning("JS Processor task not supported");
#endif
            break;
        case ProcessorTaskBase::PTT_NATIVE:
#ifdef IS_OSH_CORE_SERVICE
            return new NativeProcessorTask(id, taskType, taskTriggerType, scriptCode, runCondition, scheduleInterval, publishResult);
#else
            qWarning("Native Processor task not supported");
#endif
        break;
    }


}


LogCat::LOGCAT ModelProcessorManager::logCat() {
    return LogCat::PROCESSOR;
}

void ModelProcessorManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(DatamodelManager);
    REQUIRE_MANAGER(ServerValueManager);
    REQUIRE_MANAGER(CommunicationManagerBase);
    REQUIRE_MANAGER(ActorManager);

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);
    m_valueManager = getManager<ServerValueManager>(ServerValueManager::MANAGER_ID);
    m_actorManager = getManager<ActorManager>(ActorManager::MANAGER_ID);

    m_scheduleTimer.setInterval(config->getInt("processor.intervalMs", 100));

    m_dmManager = getManager<DatamodelManager>(DatamodelManager::MANAGER_ID);

    // init executors
    m_processorExecutors.insert(ProcessorTaskBase::PTT_NATIVE, new NativeProcessorExecutor(m_dmManager, &m_localStorage, m_valueManager, m_actorManager, this));
#ifdef PROCESSOR_JS_SUPPORT
    m_processorExecutors.insert(ProcessorTaskBase::PTT_JS, new JSProcessorExecutor(m_dmManager, &m_localStorage, m_valueManager, m_actorManager, this));
#endif

}

void ModelProcessorManager::postInit() {
    iDebug() << Q_FUNC_INFO;

    m_processorTasks = m_dmManager->datamodel()->processorTasks();

    // connect script actors
    for (ActorBase *actor : m_dmManager->datamodel()->actors()) {
        if (actor->inherits(ScriptTriggerActor::staticMetaObject.className())) {
            ScriptTriggerActor *scriptTriggerActor = static_cast<ScriptTriggerActor*>(actor);

            Helpers::safeConnect(scriptTriggerActor, &ScriptTriggerActor::triggerScript, this, &ModelProcessorManager::onTriggerScriptTask, SIGNAL(triggerScript()), SLOT(onTriggerScriptTask()));
        }
    }

    start();
}

void ModelProcessorManager::onTriggerScriptTask() {
    iInfo() << Q_FUNC_INFO;

    ScriptTriggerActor *scriptTriggerActor = static_cast<ScriptTriggerActor*>(sender());
    QString taskId = scriptTriggerActor->rawValue().toString();

    if (m_processorTasks.contains(taskId)) {
        executeTask(m_processorTasks.value(taskId));
    } else {
        iWarning() << "Invalid processor task" << taskId;
    }
}

QString ModelProcessorManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE ModelProcessorManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void ModelProcessorManager::handleReceivedMessage(MessageBase* msg) {
}

void ModelProcessorManager::start() {
    iDebug() << Q_FUNC_INFO;

    m_scheduleTimer.start();
}

void ModelProcessorManager::stop() {
    iDebug() << Q_FUNC_INFO;

    m_scheduleTimer.stop();
}

void ModelProcessorManager::executeTasks() {
    QMapIterator<QString, ProcessorTaskBase*> it(m_processorTasks);

    // first, execute all only once's
    if (m_isFirstRun) {
        while(it.hasNext()) {
            it.next();

            if (it.value()->taskTriggerType() == ProcessorTaskBase::PTTT_ONLY_ONCE) {
                if (m_isFirstRun) {
                    executeTask(it.value());
                }
            }
        }

        m_isFirstRun = false;
    }


    while(it.hasNext()) {
        it.next();

        switch(it.value()->taskTriggerType()) {
        case ProcessorTaskBase::PTTT_INTERVAL:
            if (QDateTime::currentMSecsSinceEpoch() > it.value()->lastExecution() + it.value()->scheduleInterval()) {
                executeTask(it.value());
            }
            break;
        case ProcessorTaskBase::PTTT_TRIGGER:
            // will triggered externally
            break;
        }
    }
}

void ModelProcessorManager::executeTask(ProcessorTaskBase* task) {
    iDebug() << Q_FUNC_INFO;

    if (task->isEnabled()) {
        ProcessorExecutorBase* executor = m_processorExecutors.value(task->taskType());

        QVariant result = executor->execute(task);
        //QVariant result = it.value()->run(&m_engine, m_commonScripts);
        if (task->publishResult()) {
            publishScriptResult(task->id(), result);
        }
    } else {
        iDebug() << "Skipping task, since it's not enabled" << task->id();
    }
}

void ModelProcessorManager::publishScriptResult(QString taskId, QVariant value) {
    iDebug() << Q_FUNC_INFO << taskId << value;

    ScriptResultMessage srMessage(taskId, value);
    m_commManager->sendMessage(srMessage);
}


