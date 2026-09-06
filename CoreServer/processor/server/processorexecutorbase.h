#pragma once

#include <QObject>

#include "identifyable.h"
#include "datamodel/datamodelmanager.h"
#include "localstorage.h"
#include "taskstorage.h"
#include "processor/processortaskbase.h"

#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"

#include "sharedlib.h"

class SHARED_LIB_EXPORT ProcessorExecutorBase : public QObject, public Identifyable
{
    Q_OBJECT
public:
    explicit ProcessorExecutorBase(QString id, DatamodelManager *dmManager, LocalStorage *localStorage, TaskStorage* taskStorage, ValueManagerBase* valueManager, ActorManager* actorManager, QObject *parent = nullptr);
    virtual QVariant execute(ProcessorTaskBase* task) = 0;

    /*virtual*/ LogCat::LOGCAT logCat();


protected:
    DatamodelManager *m_dmManager;
    LocalStorage *m_localStorage;
    TaskStorage *m_taskStorage;
    ValueManagerBase *m_valueManager;
    ActorManager *m_actorManager;

signals:

};

