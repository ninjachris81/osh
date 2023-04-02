#ifndef NATIVEPROCESSORTASK_H
#define NATIVEPROCESSORTASK_H

#include <QObject>

#include "processor/processortaskbase.h"

class CommonScripts;

class SHARED_LIB_EXPORT NativeProcessorTask : public ProcessorTaskBase
{
    Q_OBJECT
public:

    enum NativeModuleType {
        NMT_INVALID = 0,
        NMT_COMMON_SCRIPTS = 10
    };

    enum NativeFunctionType {
        NFT_INVALID = 0,
        NFT_INIT_SWITCH_LOGIC =                 10,
        NFT_APPLY_SWITCH_TIMEOUT_LOGIC =        11,

        NFT_APPLY_SHUTTER_LOGIC =               20,

        NFT_INIT_DOOR_RING_LOGIC =              30,
        NFT_APPLY_DOOR_RING_TIMEOUT_LOGIC =     31,

        NFT_INIT_PLAY_SOUND_ON_EVENT =          40,
        NFT_INIT_PLAY_SOUND_ON_EVENT_2 =          41,
    };

    NativeProcessorTask();
    explicit NativeProcessorTask(QString groupId, QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, int moduleCode, int functionCode, QStringList params, qint64 scheduleInterval = 0, bool publishResult = false, bool enabled = true, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;

    /*virtual*/ QVariant run() override;

    void setCommonScripts(CommonScripts* commonScripts);

    void setNativeFunction(NativeFunctionType nativeFunction);
    NativeFunctionType nativeFunction();
    void addNativeParam(QVariant value);
    QVariantList nativeParams();

    static QList<QVariant::Type> paramTypeList(NativeFunctionType nativeFunction);

private:
    bool checkRunCondition();

    NativeModuleType m_nativeModule = NMT_INVALID;
    NativeFunctionType m_nativeFunction = NFT_INVALID;
    QVariantList m_nativeParams;

    CommonScripts* m_commonScripts = nullptr;


signals:

};

#endif // NATIVEPROCESSORTASK_H
