#include "nativeprocessortask.h"
#include "processor/server/commonscripts.h"

NativeProcessorTask::NativeProcessorTask() : ProcessorTaskBase() {

}

NativeProcessorTask::NativeProcessorTask(QString id, ProcessorTaskType taskType, ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition, qint64 scheduleInterval, bool publishResult, QObject *parent) : ProcessorTaskBase(id, taskType, taskTriggerType, scriptCode, runCondition, scheduleInterval, publishResult, parent)
{

    if (scriptCode.startsWith("CommonScripts.") && scriptCode.endsWith(")")) {
        if (scriptCode.startsWith("CommonScripts.initSwitchLogic")) {
            m_nativeFunction = NativeProcessorTask::NFT_INIT_SWITCH_LOGIC;
        } else if (scriptCode.startsWith("CommonScripts.applySwitchTimeoutLogic")) {
            m_nativeFunction = NativeProcessorTask::NFT_APPLY_SWITCH_TIMEOUT_LOGIC;
        } else if (scriptCode.startsWith("CommonScripts.applyShutterLogic")) {
            m_nativeFunction = NativeProcessorTask::NFT_APPLY_SHUTTER_LOGIC;
        } else {
            qFatal("Unsupported script operation");
        }

        int start = scriptCode.indexOf("(");
        int end = scriptCode.lastIndexOf(")");

        QString params = scriptCode.mid(start + 1, end - (start + 1));
        QStringList paramTokens = params.split(",");
        QList<QVariant::Type> typeList = NativeProcessorTask::paramTypeList(m_nativeFunction);

        for (quint8 i = 0; i < paramTokens.size();i++) {
            QString str = paramTokens.at(i).trimmed();
            if (str.startsWith("'")) str = str.mid(1);
            if (str.endsWith("'")) str = str.chopped(1);

            QVariant var = QVariant::fromValue(str);
            var.convert(typeList.at(i));
            addNativeParam(var);
        }
    } else {
        iWarning() << "Unable to resolve native function" << scriptCode;
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
        case NFT_APPLY_SWITCH_TIMEOUT_LOGIC:
            m_lastResult = m_commonScripts->applySwitchTimeoutLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toInt());
            break;
        case NFT_APPLY_SHUTTER_LOGIC:
            m_lastResult = m_commonScripts->applyShutterLogic(m_nativeParams.at(0).toString(), m_nativeParams.at(1).toString(), m_nativeParams.at(2).toInt(), m_nativeParams.at(3).toInt(), m_nativeParams.at(4).toInt(), m_nativeParams.at(5).toInt());
            break;
        default:
            break;
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
        return QList<QVariant::Type>() << QVariant::String << QVariant::String << QVariant::Int << QVariant::Int << QVariant::Int << QVariant::Int;
    default:
        return QList<QVariant::Type>();
    }
}
