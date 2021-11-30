#ifndef MODELPROCESSORMANAGER_H
#define MODELPROCESSORMANAGER_H

#include <QObject>
#include <QList>
#include <QFuture>
#include <QJSEngine>
#include <QTimer>

#include "manager/managerbase.h"
#include "processor/server/processortask.h"
#include "datamodel/server/datamodelmanager.h"
#include "processor/server/scriptbase.h"
#include "communication/communicationmanagerbase.h"

class ModelProcessorManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ModelProcessorManager(QObject *parent = nullptr);

    static QLatin1Literal MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ void postInit() override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void start();

    void stop();

private:
    QJSEngine m_engine;
    QMap<QString, ProcessorTask*> m_processorTasks;
    QTimer m_scheduleTimer;

    QList<QJSValue> m_values;

    QMap<QString, ScriptBase*> m_scripts;

    CommunicationManagerBase* m_commManager;

    void injectValues(DatamodelManager *dmManager);
    void injectActors(DatamodelManager *dmManager);
    void injectConstants();
    void injectScripts();

    void injectValue(ValueBase* value);
    void injectActor(ActorBase* actor);

    void registerScript(ScriptBase* script);

    void publishScriptResult(QString taskId, QVariant value);

private slots:
    void executeTasks();

signals:

public slots:
};

#endif // MODELPROCESSORMANAGER_H
