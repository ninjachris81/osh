#include "processorvariable.h"

QLatin1String ProcessorVariable::PROPERTY_VALUE = QLatin1String("value");
QLatin1String ProcessorVariable::VARIABLE_PREFIX = QLatin1String("$");

ProcessorVariable::ProcessorVariable() {

}

ProcessorVariable::ProcessorVariable(QString id, QString value, QObject *parent)
    : QObject{parent}, Identifyable(id), m_value(value)
{
}

QString ProcessorVariable::value() {
    return m_value;
}

QString ProcessorVariable::variableId() {
    return VARIABLE_PREFIX + m_id;
}

void ProcessorVariable::replaceScriptCode(QString &scriptCode)  {
    scriptCode.replace(variableId(), m_value);
}
