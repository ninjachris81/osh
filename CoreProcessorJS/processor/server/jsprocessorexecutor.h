#ifndef JSPROCESSOREXECUTOR_H
#define JSPROCESSOREXECUTOR_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

#include "processor/server/processorexecutorbase.h"
#include "datamodel/server/datamodelmanager.h"
#include "processor/server/jsprocessortask.h"
#include "processor/server/scriptbase.h"
#include "processor/server/commonscripts.h"

class SHARED_LIB_EXPORT JSProcessorExecutor : public ProcessorExecutorBase
{
    Q_OBJECT
public:
    explicit JSProcessorExecutor(DatamodelManager *dmManager, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager *actorManager, QObject *parent = nullptr);

    /*virtual*/ QVariant execute(ProcessorTaskBase* task) override;

    /*virtual*/ class QVariant execute(JSProcessorTask* task);

private:
    QJSEngine m_engine;
    QList<QJSValue> m_values;

    QMap<QString, ScriptBase*> m_scripts;
    CommonScripts *m_commonScripts;

    void injectValue(ValueBase* value);
    void injectActor(ActorBase* actor);

    void injectValues(DatamodelManager *dmManager);
    void injectActors(DatamodelManager *dmManager);
    void injectConstants();
    void injectScripts();
    void injectLocalStorage();

    void registerScript(ScriptBase* script);

signals:

};

#endif // JSPROCESSOREXECUTOR_H
