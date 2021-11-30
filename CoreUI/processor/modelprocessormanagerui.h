#ifndef MODELPROCESSORMANAGERUI_H
#define MODELPROCESSORMANAGERUI_H

#include <QObject>
#include <QQmlEngine>
#include <QList>

#include "manager/managerbase.h"
#include "processor/processortaskui.h"

#include "datamodel/datamodelmanagerui.h"

class ModelProcessorManagerUI : public ManagerBase
{
    Q_OBJECT
public:
    explicit ModelProcessorManagerUI(QObject *parent = nullptr);

    Q_PROPERTY(QList<QObject*> processorTasks READ processorTasks NOTIFY processorTasksChanged)

    static QLatin1Literal MANAGER_ID;

    /*virtual*/ QString id() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    QList<QObject*> processorTasks();

private:
    static ModelProcessorManagerUI* m_qmlInstance;

    DatamodelManagerUI* m_datamodelManager;

signals:
    void processorTasksChanged();

public slots:
};

#endif // MODELPROCESSORMANAGERUI_H
