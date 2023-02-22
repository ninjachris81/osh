#ifndef PROCESSORTASKFACTORY_H
#define PROCESSORTASKFACTORY_H

#include <QObject>

#include "processor/processortaskbase.h"

class ProcessorTaskFactory
{
public:
    virtual ProcessorTaskBase* createProcessorTask(QString id, ProcessorTaskBase::ProcessorTaskType taskType, ProcessorTaskBase::ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult) = 0;

};

#endif // PROCESSORTASKFACTORY_H
