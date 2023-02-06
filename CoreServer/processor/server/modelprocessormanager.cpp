#include "modelprocessormanager.h"

#include <QDebug>
#include <QDateTime>
#include <QMetaEnum>
#include <QResource>
#include <QThread>

#include "macros.h"
#include "value/server/servervaluemanager.h"
#include "shared/actor_qt.h"
#include "processor/server/commonscripts.h"
#include "processor/scriptresultmessage.h"
#include "processor/server/nativeprocessorexecutor.h"

#ifdef PROCESSOR_JS_SUPPORT
    #include "processor/server/jsprocessorexecutor.h"
#endif

QLatin1String ModelProcessorManager::MANAGER_ID = QLatin1String("ModelProcessorManager");


ModelProcessorManager::ModelProcessorManager(QObject *parent) : ManagerBase(parent)
{
    connect(&m_scheduleTimer, &QTimer::timeout, this, &ModelProcessorManager::executeTasks);
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

    start();
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

    while(it.hasNext()) {
        it.next();

        ProcessorExecutorBase* executor = m_processorExecutors.value(it.value()->taskType());

        switch(it.value()->taskTriggerType()) {
        case ProcessorTaskBase::PTTT_INTERVAL:
            if (QDateTime::currentMSecsSinceEpoch() > it.value()->lastExecution() + it.value()->scheduleInterval()) {
                QVariant result = executor->execute(it.value());
                //QVariant result = it.value()->run(&m_engine, m_commonScripts);
                if (it.value()->publishResult()) {
                    publishScriptResult(it.key(), result);
                }
            }
            break;
        case ProcessorTaskBase::PTTT_ONLY_ONCE:
            if (m_isFirstRun) {
                QVariant result = executor->execute(it.value());
                //QVariant result = it.value()->run(&m_engine, m_commonScripts);
                if (it.value()->publishResult()) {
                    publishScriptResult(it.key(), result);
                }
            }
            break;
        case ProcessorTaskBase::PTTT_TRIGGER:
            // will triggered externally
            break;
        }
    }

    m_isFirstRun = false;
}

void ModelProcessorManager::publishScriptResult(QString taskId, QVariant value) {
    iDebug() << Q_FUNC_INFO << taskId << value;

    ScriptResultMessage srMessage(taskId, value);
    m_commManager->sendMessage(srMessage);
}


