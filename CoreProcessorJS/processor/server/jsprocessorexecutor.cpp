#include "jsprocessorexecutor.h"

#include <QDebug>

JSProcessorExecutor::JSProcessorExecutor(DatamodelManager *dmManager, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager *actorManager, QObject *parent)
    : ProcessorExecutorBase("JSProcessorExecutor", dmManager, localStorage, valueManager, actorManager, parent)
{
    m_engine.installExtensions(QJSEngine::AllExtensions);

    m_commonScripts = new CommonScripts(dmManager->datamodel(), localStorage, valueManager, actorManager, this);
    registerScript(m_commonScripts);

    injectValues(m_dmManager);

    injectActors(m_dmManager);

    injectConstants();

    injectLocalStorage();

    injectScripts();
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

void JSProcessorExecutor::injectValue(ValueBase* value) {
    QJSValue val = m_engine.newQObject(value);

    QString fullId = "values_" + value->valueGroup()->id() + "_" + value->id();
    iDebug() << "Injecting val" << value->fullId() << fullId;
    m_engine.globalObject().setProperty(fullId, val);
}

void JSProcessorExecutor::injectActor(ActorBase* actor) {
    QJSValue val = m_engine.newQObject(actor);

    QString fullId = "actors_" + actor->valueGroup()->id() + "_" + actor->id();
    iDebug() << "Injecting actor" << actor->fullId() << fullId;
    m_engine.globalObject().setProperty(fullId, val);

    injectValue(actor);
}

void JSProcessorExecutor::injectValues(DatamodelManager* dmManager) {
    iDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ValueBase*> it(dmManager->datamodel()->values());

    while(it.hasNext()) {
        it.next();
        injectValue(it.value());
    }
}

void JSProcessorExecutor::injectActors(DatamodelManager* dmManager) {
    iDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ActorBase*> it(dmManager->datamodel()->actors());
    while(it.hasNext()) {
        it.next();
        injectActor(it.value());
    }
}

void JSProcessorExecutor::injectConstants() {
    iDebug() << Q_FUNC_INFO;

    QJSValue constants = m_engine.newObject();

    QMetaEnum e = QMetaEnum::fromType<actor::ACTOR_CMDS>();
    for (quint8 i=0;i<e.keyCount();i++) {
        QString key = e.key(i);
        iDebug() << "Injecting constant" << key;
        constants.setProperty(key, QJSValue(e.value(i)));
    }

    m_engine.globalObject().setProperty("C", constants);
}

void JSProcessorExecutor::injectScripts() {
    iDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ScriptBase*> it(m_scripts);
    while (it.hasNext()) {
        it.next();
        iDebug() << "Injecting script" << it.key();
        QJSValue script = m_engine.newQObject(it.value());
        m_engine.globalObject().setProperty(it.key(), script);
    }
}

void JSProcessorExecutor::injectLocalStorage() {
    iDebug() << Q_FUNC_INFO;

    QJSValue localStorage = m_engine.newQObject(m_localStorage);
    m_engine.globalObject().setProperty("LocalStorage", localStorage);
}

void JSProcessorExecutor::registerScript(ScriptBase* script) {
    iDebug() << Q_FUNC_INFO << script->id();

    if (!m_scripts.contains(script->id())) {
        m_scripts.insert(script->id(), script);
    } else {
        iWarning() << "Script name is already registered" << script->id();
    }
}

