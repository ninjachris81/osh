#ifndef PROCESSORTASK_H
#define PROCESSORTASK_H

#include <QObject>
#include <QJSEngine>

#include "serializableidentifyable.h"

class ProcessorTask : public QObject, public SerializableIdentifyable
{
    Q_OBJECT
public:
    static qint64 INTERVAL_REALTIME;

    enum ProcessorTaskType {
        PTT_INTERVAL = 0,
        PTT_ONLY_ONCE = 1,
        PTT_TRIGGER = 2
    };

    ProcessorTask();
    explicit ProcessorTask(QString id, ProcessorTaskType taskType, QString scriptCode, QString runCondition = "", qint64 scheduleInterval = 0, bool publishResult = false, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;


    /*virtual*/ LogCat::LOGCAT logCat() override;

    QVariant run(QJSEngine* engine);

    QString scriptCode();
    qint64 scheduleInterval();
    ProcessorTaskType taskType();
    bool publishResult();

    qint64 lastExecution();
    QVariant lastResult();

    void setLastResult(QVariant lastResult);
    void setLastExecutionNow();

private:
    QString m_scriptCode;
    QString m_runCondition;
    qint64 m_scheduleInterval;
    bool m_publishResult = false;
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
