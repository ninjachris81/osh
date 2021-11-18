#include "digitalinputcontrollerbase.h"

DigitalInputControllerBase::DigitalInputControllerBase(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{
}

void DigitalInputControllerBase::init() {
    iDebug() << Q_FUNC_INFO;

    m_inputStatus = QBitArray(inputCount());
}

void DigitalInputControllerBase::handleMessage(ControllerMessage *msg) {

}

bool DigitalInputControllerBase::inputStatus(quint8 valueIndex) {
    return m_inputStatus.at(valueIndex);
}

quint8 DigitalInputControllerBase::bindValue(BooleanValue *value) {
    quint8 valueIndex = m_valueMappings.count();
    m_valueMappings.insert(valueIndex, value);
    return valueIndex;
}
