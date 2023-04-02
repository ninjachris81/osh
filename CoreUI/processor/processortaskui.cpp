#include "processortaskui.h"

ProcessorTaskUI::ProcessorTaskUI(Identifyable *parent) : IdentifyableUI(parent)
{
    m_processorTask = static_cast<ProcessorTaskBase*>(parent);

    connect(m_processorTask, &ProcessorTaskBase::lastExecutionChanged, this, &ProcessorTaskUI::lastExecutionChanged);
    connect(m_processorTask, &ProcessorTaskBase::lastResultChanged, this, &ProcessorTaskUI::lastResultChanged);
}

/*
QString ProcessorTaskUI::scriptCode() {
    return m_processorTask->scriptCode();
}
*/

qint64 ProcessorTaskUI::scheduleInterval() {
    return m_processorTask->scheduleInterval();
}

qint64 ProcessorTaskUI::lastExecution() {
    return m_processorTask->lastExecution();
}

QVariant ProcessorTaskUI::lastResult() {
    return m_processorTask->lastResult();
}

void ProcessorTaskUI::setLastResult(QVariant lastResult) {
    m_processorTask->setLastResult(lastResult);
    m_processorTask->setLastExecutionNow();
}
