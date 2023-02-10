#ifndef PROCESSOREXECUTORBASE_H
#define PROCESSOREXECUTORBASE_H

#include <QObject>

#include "identifyable.h"
#include "datamodel/server/datamodelmanager.h"
#include "processor/server/localstorage.h"
#include "processor/server/processortaskbase.h"

#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"

#include "sharedlib.h"

class SHARED_LIB_EXPORT ProcessorExecutorBase : public QObject, public Identifyable
{
    Q_OBJECT
public:
    explicit ProcessorExecutorBase(QString id, DatamodelManager *dmManager, LocalStorage *localStorage, ValueManagerBase* valueManager, ActorManager* actorManager, QObject *parent = nullptr);
    virtual QVariant execute(ProcessorTaskBase* task) = 0;

    /*virtual*/ LogCat::LOGCAT logCat();


protected:
    DatamodelManager *m_dmManager;
    LocalStorage *m_localStorage;
    ValueManagerBase *m_valueManager;
    ActorManager *m_actorManager;

signals:

};

#endif // PROCESSOREXECUTORBASE_H
