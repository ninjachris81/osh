#ifndef MODELPROCESSORMANAGER_H
#define MODELPROCESSORMANAGER_H

#include <QObject>
#include <QList>
#include <QFuture>
#include <QTimer>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "datamodel/datamodelmanager.h"
#include "processor/server/scriptbase.h"
#include "communication/communicationmanagerbase.h"
#include "processor/server/localstorage.h"
#include "processor/server/commonscripts.h"
#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"
#include "processor/server/processorexecutorbase.h"
#include "processor/server/nativeprocessortask.h"


class SHARED_LIB_EXPORT ModelProcessorManager : public ManagerBase, public ProcessorTaskFactory
{
    Q_OBJECT
public:
    explicit ModelProcessorManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    ProcessorTaskBase* createProcessorTask(QString groupId, QString id, ProcessorTaskBase::ProcessorTaskType taskType, ProcessorTaskBase::ProcessorTaskTriggerType taskTriggerType, int functionCode, QStringList params, qint64 scheduleInterval) override;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ void postInit() override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void start();

    void stop();

    void executeTask(ProcessorTaskBase* task);

private:
    QMap<ProcessorTaskBase::ProcessorTaskType, ProcessorExecutorBase*> m_processorExecutors;
    QMap<QString, ProcessorTaskBase*> m_processorTasks;
    QTimer m_scheduleTimer;

    LocalStorage m_localStorage;

    CommunicationManagerBase* m_commManager;
    DatamodelManager* m_dmManager;
    ValueManagerBase* m_valueManager;
    ActorManager* m_actorManager;
    bool m_isFirstRun = true;

    void publishScriptResult(QString taskId, QVariant value);

private slots:
    void executeTasks();
    void onTriggerScriptTask();

signals:

public slots:
};

#endif // MODELPROCESSORMANAGER_H
