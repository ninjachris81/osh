#ifndef PROCESSORTASKBASE_H
#define PROCESSORTASKBASE_H

#include <QObject>

#include "sharedlib.h"

#include "serializableidentifyable.h"

class SHARED_LIB_EXPORT ProcessorTaskBase : public QObject, public SerializableIdentifyable
{
    Q_OBJECT
public:
    static qint64 INTERVAL_REALTIME;

    static QLatin1String PROPERTY_GROUP_ID;
    static QLatin1String PROPERTY_TASK_TYPE;
    static QLatin1String PROPERTY_TASK_TRIGGER_TYPE;
    static QLatin1String PROPERTY_SCRIPT_CODE;
    static QLatin1String PROPERTY_RUN_CONDITION;
    static QLatin1String PROPERTY_SCHEDULE_INTERVAL;
    static QLatin1String PROPERTY_PUBLISH_RESULT;
    static QLatin1String PROPERTY_ENABLED;

    enum ProcessorTaskTriggerType {
        PTTT_INTERVAL = 0,
        PTTT_ONLY_ONCE = 1,
        PTTT_TRIGGER = 2
    };

    enum ProcessorTaskType {
        PTT_JS = 0,
        PTT_NATIVE = 1
    };

    ProcessorTaskBase();
    explicit ProcessorTaskBase(QString groupId, QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition = "", qint64 scheduleInterval = 0, bool publishResult = false, bool enabled = true, QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    virtual QVariant run() = 0;

    QString scriptCode();
    qint64 scheduleInterval();
    ProcessorTaskType taskType();
    ProcessorTaskTriggerType taskTriggerType();
    bool publishResult();
    bool isEnabled();
    QString groupId();

    qint64 lastExecution();
    QVariant lastResult();

    void setLastResult(QVariant lastResult);
    void setLastExecutionNow();
    void setEnabled(bool enabled);

protected:
    ProcessorTaskType m_processorTaskType = PTT_JS;
    ProcessorTaskTriggerType m_processorTaskTriggerType = PTTT_INTERVAL;

    QString m_scriptCode;
    QString m_runCondition;
    qint64 m_scheduleInterval;
    bool m_publishResult = false;
    bool m_enabled = true;
    QString m_groupId;

    qint64 m_lastExecution = 0;
    QVariant m_lastResult;

signals:
    void lastExecutionChanged();
    void lastResultChanged();


};

#endif // PROCESSORTASKBASE_H
