#ifndef JSPROCESSORTASK_H
#define JSPROCESSORTASK_H

#include <QObject>
#include <QJSEngine>

#include "sharedlib.h"

#include "processor/server/processortaskbase.h"

class SHARED_LIB_EXPORT JSProcessorTask : public ProcessorTaskBase
{
    Q_OBJECT
public:

    JSProcessorTask();
    explicit JSProcessorTask(QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition = "", qint64 scheduleInterval = 0, bool publishResult = false, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;

    QVariant run() override;

    void setEngine(QJSEngine* engine);



private:
    QJSEngine* m_engine = nullptr;

    bool checkRunCondition(QJSEngine *engine);

signals:

public slots:
};

#endif // JSPROCESSORTASK_H
