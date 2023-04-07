#include "valueactor.h"

ValueActor::ValueActor(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QVariant::Type typeHint, QObject *parent)
    : ActorBase(valueGroup, id, valueType, typeHint, parent)
{

}

bool ValueActor::cmdSupported(actor::ACTOR_CMDS cmd) {
    return cmd == actor::ACTOR_CMD_SET_VALUE;
}

bool ValueActor::isAsync() {
    return true;
}

void ValueActor::_triggerCmd(actor::ACTOR_CMDS cmd) {
    if (cmd == actor::ACTOR_CMD_SET_VALUE) {
        Q_EMIT(requestSetValue());
    }
}

QVariant ValueActor::_updateValue(QVariant newValue) {
    if (newValue.canConvert(m_typeHint)) {
        newValue.convert(m_typeHint);
        return newValue;
    } else {
        qWarning() << "Cannot convert" << newValue << "to type" << m_typeHint;
        return QVariant::fromValue(newValue);
    }
}
