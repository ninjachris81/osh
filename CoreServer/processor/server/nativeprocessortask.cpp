#include "nativeprocessortask.h"
#include "processor/server/commonscripts.h"

NativeProcessorTask::NativeProcessorTask() : ProcessorTaskBase() {

}

NativeProcessorTask::NativeProcessorTask(QString groupId, QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, int moduleCode, int functionCode, QStringList params, qint64 scheduleInterval, bool publishResult, bool enabled, QObject *parent)
    :ProcessorTaskBase(groupId, id, taskType, taskTriggerType, moduleCode, functionCode, params, scheduleInterval, enabled, parent)
{
    m_nativeModule = static_cast<NativeModuleType>(m_moduleCode);
    m_nativeFunction = static_cast<NativeFunctionType>(m_functionCode);

    QList<QVariant::Type> typeList = NativeProcessorTask::paramTypeList(m_nativeFunction);

    for (quint8 i = 0; i < m_paramList.size();i++) {
        QString str = m_paramList.at(i).trimmed();
        if (str.startsWith("'")) str = str.mid(1);
        if (str.endsWith("'")) str = str.chopped(1);

        QVariant var = QVariant::fromValue(str);
        if (typeList.at(i) != QVariant::UserType) {     // UserType = don't convert
            var.convert(typeList.at(i));
        }
        addNativeParam(var);
    }
}


void NativeProcessorTask::serialize(QJsonObject &obj) {
    ProcessorTaskBase::serialize(obj);
}

void NativeProcessorTask::deserialize(QJsonObject obj) {
    ProcessorTaskBase::deserialize(obj);
}

QString NativeProcessorTask::getClassName() {
    return staticMetaObject.className();
}

QVariant NativeProcessorTask::run() {
    iDebug() << Q_FUNC_INFO;

    if (m_commonScripts == nullptr) {
        iWarning() << "No scripts object";
        return false;
    }

    if (checkRunCondition()) {
        switch(m_nativeModule) {
        case NMT_COMMON_SCRIPTS:

            switch(m_nativeFunction) {
            case NFT_INIT_SWITCH_LOGIC:
                m_lastResult = m_commonScripts->initSwitchLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toString());
                break;
            case NFT_APPLY_SWITCH_TIMEOUT_LOGIC:
                m_lastResult = m_commonScripts->applySwitchTimeoutLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toInt());
                break;
            case NFT_APPLY_SHUTTER_LOGIC:
                m_lastResult = m_commonScripts->applyShutterLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toString(), m_nativeParams.at(3).toInt(), m_nativeParams.at(4).toInt(), m_nativeParams.at(5).toInt(), m_nativeParams.at(6).toInt());
                break;
            case NFT_INIT_DOOR_RING_LOGIC:
                m_lastResult = m_commonScripts->initDoorRingLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString());
                break;
            case NFT_APPLY_DOOR_RING_TIMEOUT_LOGIC:
                m_lastResult = m_commonScripts->applyDoorRingTimeoutLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toLongLong());
                break;
            case NFT_INIT_PLAY_SOUND_ON_EVENT:
                m_lastResult = m_commonScripts->initPlaySoundOnEvent(m_nativeParams.at(0).toString(), m_nativeParams.at(1), m_nativeParams.at(2).toString(), m_nativeParams.at(3).toString());
                break;
            case NFT_INIT_PLAY_SOUND_ON_EVENT_2:
                m_lastResult = m_commonScripts->initPlaySoundOnEvent2(m_nativeParams.at(0).toString(), m_nativeParams.at(1), m_nativeParams.at(2), m_nativeParams.at(3).toString(), m_nativeParams.at(4).toString());
                break;
            default:
                iWarning() << "Unhandled script function" << m_nativeFunction;
                break;
            }
            break;

        default:
            iWarning() << "Invalid native module" << m_nativeModule;
            Q_ASSERT(false);
        }

        Q_EMIT(lastResultChanged());

        setLastExecutionNow();

        return m_lastResult;
    }

    return false;
}

void NativeProcessorTask::setCommonScripts(CommonScripts* commonScripts) {
    m_commonScripts = commonScripts;
}

void NativeProcessorTask::setNativeFunction(NativeProcessorTask::NativeFunctionType nativeFunction) {
    m_nativeFunction = nativeFunction;
}

NativeProcessorTask::NativeFunctionType NativeProcessorTask::nativeFunction() {
    return m_nativeFunction;
}

void NativeProcessorTask::addNativeParam(QVariant value) {
    iDebug() << Q_FUNC_INFO << value;

    m_nativeParams.append(value);
}

QVariantList NativeProcessorTask::nativeParams() {
    return m_nativeParams;
}

bool NativeProcessorTask::checkRunCondition() {
    // TODO
    return true;
}

QList<QVariant::Type> NativeProcessorTask::paramTypeList(NativeProcessorTask::NativeFunctionType nativeFunction) {
    switch(nativeFunction) {
    case NativeProcessorTask::NFT_INIT_SWITCH_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_APPLY_SWITCH_TIMEOUT_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::Int;
    case NativeProcessorTask::NFT_APPLY_SHUTTER_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::String << QVariant::Int << QVariant::Int << QVariant::Int << QVariant::Int;
    case NativeProcessorTask::NFT_INIT_DOOR_RING_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_APPLY_DOOR_RING_TIMEOUT_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::LongLong;
    case NativeProcessorTask::NFT_INIT_PLAY_SOUND_ON_EVENT:
        return QList<QVariant::Type>() << QVariant::String << QVariant::UserType << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_INIT_PLAY_SOUND_ON_EVENT_2:
        return QList<QVariant::Type>() << QVariant::String << QVariant::UserType << QVariant::UserType << QVariant::String << QVariant::String;
    default:
        return QList<QVariant::Type>();
    }
}
