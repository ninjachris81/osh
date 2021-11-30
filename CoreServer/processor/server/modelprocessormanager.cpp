#include "modelprocessormanager.h"

#include <QDebug>
#include <QDateTime>
#include <QMetaEnum>
#include <QResource>
#include <QQmlEngine>

#include "macros.h"
#include "value/server/servervaluemanager.h"
#include "shared/actor_qt.h"
#include "processor/server/commonscripts.h"
#include "processor/scriptresultmessage.h"

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
    REQUIRE_MANAGER(CommunicationManagerBase);

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);

    m_scheduleTimer.setInterval(config->getInt("processor.intervalMs", 100));

    registerScript(new CommonScripts(&m_engine));
}

void ModelProcessorManager::postInit() {
    iDebug() << Q_FUNC_INFO;

    DatamodelManager* dmManager = getManager<DatamodelManager>(DatamodelManager::MANAGER_ID);
    m_processorTasks = dmManager->datamodel()->processorTasks();

    m_engine.installExtensions(QJSEngine::AllExtensions);

    injectValues(dmManager);

    injectActors(dmManager);

    injectConstants();

    injectScripts();

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
            QVariant result = it.value()->run(&m_engine);
            publishScriptResult(it.key(), result);
        }
    }
}

void ModelProcessorManager::publishScriptResult(QString taskId, QVariant value) {
    ScriptResultMessage srMessage(taskId, value);
    m_commManager->sendMessage(srMessage);
}

void ModelProcessorManager::registerScript(ScriptBase* script) {
    iDebug() << Q_FUNC_INFO << script->id();

    if (!m_scripts.contains(script->id())) {
        m_scripts.insert(script->id(), script);
    } else {
        iWarning() << "Script name is already registered" << script->id();
    }
}

void ModelProcessorManager::injectValue(ValueBase* value) {
    QJSValue val = m_engine.newQObject(value);

    QString fullId = "values_" + value->valueGroup()->id() + "_" + value->id();
    iDebug() << "Injecting val" << value->fullId() << fullId;
    m_engine.globalObject().setProperty(fullId, val);
}

void ModelProcessorManager::injectActor(ActorBase* actor) {
    QJSValue val = m_engine.newQObject(actor);

    QString fullId = "actors_" + actor->valueGroup()->id() + "_" + actor->id();
    iDebug() << "Injecting actor" << actor->fullId() << fullId;
    m_engine.globalObject().setProperty(fullId, val);

    injectValue(actor);
}

void ModelProcessorManager::injectValues(DatamodelManager* dmManager) {
    QMapIterator<QString, ValueBase*> it(dmManager->datamodel()->values());

    while(it.hasNext()) {
        it.next();
        injectValue(it.value());
    }
}

void ModelProcessorManager::injectActors(DatamodelManager* dmManager) {
    QMapIterator<QString, ActorBase*> it(dmManager->datamodel()->actors());
    while(it.hasNext()) {
        it.next();
        injectActor(it.value());
    }
}

void ModelProcessorManager::injectConstants() {
    QJSValue constants = m_engine.newObject();

    QMetaEnum e = QMetaEnum::fromType<actor::ACTOR_CMDS>();
    for (quint8 i=0;i<e.keyCount();i++) {
        QString key = e.key(i);
        iDebug() << "Injecting constant" << key;
        constants.setProperty(key, QJSValue(e.value(i)));
    }

    m_engine.globalObject().setProperty("C", constants);
}

void ModelProcessorManager::injectScripts() {
    QMapIterator<QString, ScriptBase*> it(m_scripts);
    while (it.hasNext()) {
        it.next();
        iDebug() << "Injecting script" << it.key();
        QJSValue script = m_engine.newQObject(it.value());
        m_engine.globalObject().setProperty(it.key(), script);
    }
}
