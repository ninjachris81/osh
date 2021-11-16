#include "modelprocessormanager.h"

#include <QDebug>
#include <QDateTime>

#include "macros.h"
#include "datamodel/server/datamodelmanager.h"
#include "value/server/servervaluemanager.h"

QLatin1Literal ModelProcessorManager::MANAGER_ID = QLatin1Literal("ModelProcessorManager");


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

    m_scheduleTimer.setInterval(config->getInt("processor.intervalMs", 100));
}

void ModelProcessorManager::postInit() {
    iDebug() << Q_FUNC_INFO;

    DatamodelManager* dmManager = getManager<DatamodelManager>(DatamodelManager::MANAGER_ID);
    m_processorTasks = dmManager->datamodel()->processorTasks();

    m_engine.installExtensions(QJSEngine::ConsoleExtension);

    QMapIterator<QString, ValueBase*> it(dmManager->datamodel()->values());
    while(it.hasNext()) {
        it.next();
        QJSValue val = m_engine.newQObject(it.value());

        iDebug() << "Injecting val" << it.key();
        m_engine.globalObject().setProperty(it.value()->id(), val);
    }

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
    QMapIterator<QString, ProcessorTask*> it(m_processorTasks);

    while(it.hasNext()) {
        it.next();

        if (QDateTime::currentMSecsSinceEpoch() > it.value()->lastExecution() + it.value()->scheduleInterval()) {
            it.value()->run(&m_engine);
        }
    }
}
