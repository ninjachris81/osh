#ifndef JSPROCESSOREXECUTOR_H
#define JSPROCESSOREXECUTOR_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

#include "processor/server/processorexecutorbase.h"
#include "datamodel/datamodelmanager.h"
#include "processor/server/jsprocessortask.h"
#include "processor/server/scriptbase.h"
#include "processor/server/jsmethods.h"

class SHARED_LIB_EXPORT JSProcessorExecutor : public ProcessorExecutorBase
{
    Q_OBJECT
public:
    explicit JSProcessorExecutor(DatamodelManager *dmManager, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager *actorManager, QObject *parent = nullptr);

    /*virtual*/ QVariant execute(ProcessorTaskBase* task) override;

    QVariant execute(JSProcessorTask* task);

private:
    JSMethods *m_jsMethods;
    QJSEngine m_engine;

signals:

};

#endif // JSPROCESSOREXECUTOR_H
