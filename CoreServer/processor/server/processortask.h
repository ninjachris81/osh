#ifndef PROCESSORTASK_H
#define PROCESSORTASK_H

#include <QObject>
#include <QJSEngine>

#include "sharedlib.h"

#include "serializableidentifyable.h"

class CommonScripts;

class SHARED_LIB_EXPORT ProcessorTask : public QObject, public SerializableIdentifyable
{
    Q_OBJECT
public:
    static qint64 INTERVAL_REALTIME;

    enum ProcessorTaskTriggerType {
        PTTT_INTERVAL = 0,
        PTTT_ONLY_ONCE = 1,
        PTTT_TRIGGER = 2
    };

    enum ProcessorTaskType {
        PTT_JS = 0,
        PTT_NATIVE = 1
    };

    enum NativeFunctionType {
        NFT_INVALID = 0,
        NFT_APPLY_SWITCH_LOGIC = 1
    };

    ProcessorTask();
    explicit ProcessorTask(QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition = "", qint64 scheduleInterval = 0, bool publishResult = false, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;


    /*virtual*/ LogCat::LOGCAT logCat() override;

    QVariant run(QJSEngine* engine, CommonScripts *commonScripts);

    QString scriptCode();
    qint64 scheduleInterval();
    ProcessorTaskType taskType();
    ProcessorTaskTriggerType taskTriggerType();
    bool publishResult();

    qint64 lastExecution();
    QVariant lastResult();

    void setLastResult(QVariant lastResult);
    void setLastExecutionNow();

    void setNativeFunction(NativeFunctionType nativeFunction);
    NativeFunctionType nativeFunction();
    void addNativeParam(QVariant value);
    QVariantList nativeParams();

    static QList<QVariant::Type> paramTypeList(NativeFunctionType nativeFunction);

private:
    QString m_scriptCode;
    QString m_runCondition;
    qint64 m_scheduleInterval;
    bool m_publishResult = false;
    ProcessorTaskType m_processorTaskType = PTT_JS;
    ProcessorTaskTriggerType m_processorTaskTriggerType = PTTT_INTERVAL;

    NativeFunctionType m_nativeFunction = NFT_INVALID;
    QVariantList m_nativeParams;

    qint64 m_lastExecution = 0;
    QVariant m_lastResult;

    bool checkRunCondition(QJSEngine *engine);

signals:
    void lastExecutionChanged();
    void lastResultChanged();

public slots:
};

#endif // PROCESSORTASK_H
