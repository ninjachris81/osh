#ifndef MODELPROCESSORMANAGER_H
#define MODELPROCESSORMANAGER_H

#include <QObject>
#include <QList>
#include <QFuture>
#include <QJSEngine>
#include <QTimer>

#include "manager/managerbase.h"
#include "processor/server/processortask.h"

class ModelProcessorManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ModelProcessorManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ void postInit();

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    void start();

    void stop();

private:
    QJSEngine m_engine;
    QMap<QString, ProcessorTask*> m_processorTasks;
    QTimer m_scheduleTimer;

private slots:
    void executeTasks();

signals:

public slots:
};

#endif // MODELPROCESSORMANAGER_H
