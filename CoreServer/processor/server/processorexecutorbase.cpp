#include "processorexecutorbase.h"

ProcessorExecutorBase::ProcessorExecutorBase(QString id, DatamodelManager *dmManager, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager *actorManager, QObject *parent)
    : QObject(parent), Identifyable(id), m_dmManager(dmManager), m_localStorage(localStorage), m_valueManager(valueManager), m_actorManager(actorManager)
{

}

LogCat::LOGCAT ProcessorExecutorBase::logCat() {
    return LogCat::PROCESSOR;
}
