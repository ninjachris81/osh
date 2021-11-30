#include "scriptresultmessage.h"

ScriptResultMessage::ScriptResultMessage(QString processorTaskId, QVariant value, QObject *parent) : MessageBase(parent), m_processorTaskId(processorTaskId), m_value(value)
{

}

MessageBase::MESSAGE_TYPE ScriptResultMessage::getMessageType() {
    return MessageBase::MESSAGE_TYPE_SCRIPT_RESULT;
}

QString ScriptResultMessage::getFirstLevelId() {
    return m_processorTaskId;
}

QString ScriptResultMessage::getSecondLevelId() {
    return "";
}

QString ScriptResultMessage::processorTaskId() {
    return m_processorTaskId;
}

QVariant ScriptResultMessage::value() {
    return m_value;
}
