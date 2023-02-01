#include "digitalinputcontrollersimulator.h"

DigitalInputControllerSimulator::DigitalInputControllerSimulator(ControllerManager *manager, QString id, QObject *parent) : DigitalInputControllerBase(manager, id, parent)
{
}

void DigitalInputControllerSimulator::init() {
    iDebug() << Q_FUNC_INFO;

    m_inputStatus = QBitArray(inputCount());
}


quint8 DigitalInputControllerSimulator::inputCount() {
    return 4;
}

void DigitalInputControllerSimulator::setStatus(quint8 valueIndex, bool value) {
    Q_ASSERT(valueIndex < inputCount());
    m_valueMappings.at(valueIndex)->updateValue(value);
}
