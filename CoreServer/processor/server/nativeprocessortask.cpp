#include "nativeprocessortask.h"
#include "processor/server/commonscripts.h"
#include "processor/server/advancedscripts.h"

NativeProcessorTask::NativeProcessorTask() : ProcessorTaskBase() {

}

NativeProcessorTask::NativeProcessorTask(QString groupId, QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, int functionCode, QStringList params, qint64 scheduleInterval, bool publishResult, bool enabled, QObject *parent)
    :ProcessorTaskBase(groupId, id, taskType, taskTriggerType, functionCode, params, scheduleInterval, enabled, parent)
{
    Q_UNUSED(publishResult)

    m_nativeFunction = static_cast<NativeFunctionType>(m_functionCode);

    QList<QVariant::Type> typeList = NativeProcessorTask::paramTypeList(m_nativeFunction);

    for (quint8 i = 0; i < typeList.size();i++) {
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
        switch(m_nativeFunction) {
        case NFT_INIT_SWITCH_LOGIC:
            m_lastResult = m_commonScripts->initSwitchLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toString());
            break;
        case NFT_INIT_SWITCH_LOGIC2:
            m_lastResult = m_commonScripts->initSwitchLogic2(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString());
            break;
        case NFT_APPLY_SWITCH_TIMEOUT_LOGIC:
            m_lastResult = m_commonScripts->applySwitchTimeoutLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toInt());
            break;
        case NFT_INIT_SWITCH_PRESENCE_LOGIC:
            m_lastResult = m_commonScripts->initSwitchPresenceLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toString(), m_nativeParams.at(3).toDouble(), m_nativeParams.at(4).toLongLong());
            break;
        case NFT_APPLY_SWITCH_PRESENCE_LOGIC:
            m_lastResult = m_commonScripts->applySwitchPresenceLogic(m_nativeParams.at(0).toString());
            break;
        case NFT_INIT_PRESENCE_LOGIC:
            m_lastResult = m_commonScripts->initPresenceLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toString());
            break;
        case NFT_APPLY_PRESENCE_LOGIC:
            m_lastResult = m_commonScripts->applyPresenceLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toLongLong());
            break;
        case NFT_APPLY_SHUTTER_LOGIC:
            m_lastResult = m_commonScripts->applyShutterLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toString(), m_nativeParams.at(3).toInt(), m_nativeParams.at(4).toInt(), m_nativeParams.at(5).toInt(), m_nativeParams.at(6).toInt());
            break;
        case NFT_APPLY_SHUTTER_LOGIC_ADV:
            m_lastResult = m_advScripts->applyShutterLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toString(), m_nativeParams.at(3).toDouble(), m_nativeParams.at(4).toDouble(), m_nativeParams.at(5).toInt(), m_nativeParams.at(6).toInt(), m_nativeParams.at(7).toInt());
            break;
        case NFT_INIT_DOOR_RING_LOGIC:
            m_lastResult = m_commonScripts->initDoorRingLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString());
            break;
        case NFT_APPLY_DOOR_RING_TIMEOUT_LOGIC:
            m_lastResult = m_commonScripts->applyDoorRingTimeoutLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toLongLong());
            break;
        case NFT_INIT_PLAY_SOUND_ON_VALUE:
            m_lastResult = m_commonScripts->initPlaySoundOnValue(m_nativeParams.at(0).toString(), m_nativeParams.at(1), m_nativeParams.at(2).toString(), m_nativeParams.at(3).toString());
            break;
        case NFT_INIT_PLAY_SOUND_ON_VALUE_2:
            m_lastResult = m_commonScripts->initPlaySoundOnValue2(m_nativeParams.at(0).toString(), m_nativeParams.at(1), m_nativeParams.at(2), m_nativeParams.at(3).toString(), m_nativeParams.at(4).toString());
            break;
        case NFT_INIT_PLAY_SOUND_ON_CMD:
            m_lastResult = m_commonScripts->initPlaySoundOnCmd(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toInt(), m_nativeParams.at(2).toString(), m_nativeParams.at(3).toString());
            break;
        case NFT_INIT_CONNECT_VALUES:
            m_lastResult = m_basicScripts->initConnectValues(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString());
            break;
        case NFT_INIT_TRIGGER_CMD_ON_VALUE:
            m_lastResult = m_basicScripts->initTriggerCmdOnValue(m_nativeParams.at(0).toString(), m_nativeParams.at(1), m_nativeParams.at(2).toString(), m_nativeParams.at(3).toInt());
            break;            
        case NFT_INIT_FOLLOW_ACTOR:
            m_lastResult = m_basicScripts->initFollowActor(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toInt());
            break;
        default:
            iWarning() << "Unhandled script function" << m_nativeFunction;
            break;
        }

        Q_EMIT(lastResultChanged());

        setLastExecutionNow();

        return m_lastResult;
    }

    return false;
}

void NativeProcessorTask::setScripts(BasicScripts* basicScripts, CommonScripts* commonScripts, AdvancedScripts* advScripts) {
    m_basicScripts = basicScripts;
    m_commonScripts = commonScripts;
    m_advScripts = advScripts;
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
    case NativeProcessorTask::NFT_INIT_SWITCH_LOGIC2:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_APPLY_SWITCH_TIMEOUT_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::Int;
    case NativeProcessorTask::NFT_INIT_SWITCH_PRESENCE_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::String << QVariant::Double << QVariant::LongLong;
    case NativeProcessorTask::NFT_APPLY_SWITCH_PRESENCE_LOGIC:
        return QList<QVariant::Type>() << QVariant::String;
    case NativeProcessorTask::NFT_INIT_PRESENCE_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_APPLY_PRESENCE_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::Int;
    case NativeProcessorTask::NFT_APPLY_SHUTTER_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::String << QVariant::Int << QVariant::Int << QVariant::Int << QVariant::Int;
    case NativeProcessorTask::NFT_APPLY_SHUTTER_LOGIC_ADV:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::String << QVariant::Double<< QVariant::Double << QVariant::Int << QVariant::Int << QVariant::Int;
    case NativeProcessorTask::NFT_INIT_DOOR_RING_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_APPLY_DOOR_RING_TIMEOUT_LOGIC:
        return QList<QVariant::Type>() << QVariant::String << QVariant::LongLong;
    case NativeProcessorTask::NFT_INIT_PLAY_SOUND_ON_VALUE:
        return QList<QVariant::Type>() << QVariant::String << QVariant::UserType << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_INIT_PLAY_SOUND_ON_VALUE_2:
        return QList<QVariant::Type>() << QVariant::String << QVariant::UserType << QVariant::UserType << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_INIT_PLAY_SOUND_ON_CMD:
        return QList<QVariant::Type>() << QVariant::String << QVariant::Int << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_INIT_CONNECT_VALUES:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String;
    case NativeProcessorTask::NFT_INIT_TRIGGER_CMD_ON_VALUE:
        return QList<QVariant::Type>() << QVariant::String << QVariant::UserType << QVariant::String << QVariant::Int;
    case NativeProcessorTask::NFT_INIT_FOLLOW_ACTOR:
        return QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::Int;
    default:
        return QList<QVariant::Type>();
    }
}
