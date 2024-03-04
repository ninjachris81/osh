#ifndef NATIVEPROCESSOREXECUTOR_H
#define NATIVEPROCESSOREXECUTOR_H

#include <QObject>

#include "processor/server/processorexecutorbase.h"
#include "processor/server/nativeprocessortask.h"
#include "processor/server/commonscripts.h"
#include "processor/server/advancedscripts.h"

class NativeProcessorExecutor : public ProcessorExecutorBase
{
    Q_OBJECT
public:
    explicit NativeProcessorExecutor(DatamodelManager *dmManager, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager *actorManager, QObject *parent = nullptr);

    /*virtual*/ QVariant execute(ProcessorTaskBase* task) override;

    QVariant execute(NativeProcessorTask* task);

private:
    BasicScripts* m_basicScripts;
    CommonScripts* m_commonScripts;
    AdvancedScripts* m_advScripts;

signals:

};

#endif // NATIVEPROCESSOREXECUTOR_H
