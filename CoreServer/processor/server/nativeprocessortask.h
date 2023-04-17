#ifndef NATIVEPROCESSORTASK_H
#define NATIVEPROCESSORTASK_H

#include <QObject>

#include "processor/processortaskbase.h"
#include "processor/server/basicscripts.h"

class CommonScripts;

class SHARED_LIB_EXPORT NativeProcessorTask : public ProcessorTaskBase
{
    Q_OBJECT
public:

    /*
    enum NativeModuleType {
        NMT_INVALID = 0,
        NMT_BASIC_SCRIPTS =         10,
        NMT_COMMON_SCRIPTS =        11
    };
    */

    enum NativeFunctionType {
        NFT_INVALID = 0,
        NFT_INIT_SWITCH_LOGIC =                 100,
        NFT_APPLY_SWITCH_TIMEOUT_LOGIC =        101,
        NFT_INIT_SWITCH_PRESENCE_LOGIC =        105,
        NFT_APPLY_SWITCH_PRESENCE_LOGIC =       106,

        NFT_INIT_PRESENCE_LOGIC =               110,
        NFT_APPLY_PRESENCE_LOGIC =              111,

        NFT_APPLY_SHUTTER_LOGIC =               120,

        NFT_INIT_DOOR_RING_LOGIC =              130,
        NFT_APPLY_DOOR_RING_TIMEOUT_LOGIC =     131,

        NFT_INIT_PLAY_SOUND_ON_VALUE =          140,
        NFT_INIT_PLAY_SOUND_ON_VALUE_2 =        141,
        NFT_INIT_PLAY_SOUND_ON_CMD =            142,

        NFT_INIT_CONNECT_VALUES =               10,
        NFT_INIT_TRIGGER_CMD_ON_VALUE =         11
    };

    NativeProcessorTask();
    explicit NativeProcessorTask(QString groupId, QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, int functionCode, QStringList params, qint64 scheduleInterval = 0, bool publishResult = false, bool enabled = true, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;

    /*virtual*/ QVariant run() override;

    void setBasicScripts(BasicScripts* basicScripts);
    void setCommonScripts(CommonScripts* commonScripts);

    void setNativeFunction(NativeFunctionType nativeFunction);
    NativeFunctionType nativeFunction();
    void addNativeParam(QVariant value);
    QVariantList nativeParams();

    static QList<QVariant::Type> paramTypeList(NativeFunctionType nativeFunction);

private:
    bool checkRunCondition();

    NativeFunctionType m_nativeFunction = NFT_INVALID;
    QVariantList m_nativeParams;

    BasicScripts* m_basicScripts = nullptr;
    CommonScripts* m_commonScripts = nullptr;


signals:

};

#endif // NATIVEPROCESSORTASK_H
