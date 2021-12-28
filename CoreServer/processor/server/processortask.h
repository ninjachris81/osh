#ifndef PROCESSORTASK_H
#define PROCESSORTASK_H

#include <QObject>
#include <QJSEngine>

#include "identifyable.h"

class ProcessorTask : public Identifyable
{
    Q_OBJECT
public:
    enum ProcessorTaskType {
        PTT_INTERVAL = 0,
        PTT_ONLY_ONCE = 1,
        PTT_TRIGGER = 2
    };

    explicit ProcessorTask(QString id, ProcessorTaskType taskType, QString scriptCode, QString runCondition = "", qint64 scheduleInterval = 0, QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    QVariant run(QJSEngine* engine);

    QString scriptCode();
    qint64 scheduleInterval();
    ProcessorTaskType taskType();

    qint64 lastExecution();
    QVariant lastResult();

    void setLastResult(QVariant lastResult);
    void setLastExecutionNow();

private:
    QString m_scriptCode;
    QString m_runCondition;
    qint64 m_scheduleInterval;
    ProcessorTaskType m_processorTaskType = PTT_INTERVAL;

    qint64 m_lastExecution = 0;
    QVariant m_lastResult;

    bool checkRunCondition(QJSEngine *engine);

signals:
    void lastExecutionChanged();
    void lastResultChanged();

public slots:
};

#endif // PROCESSORTASK_H
