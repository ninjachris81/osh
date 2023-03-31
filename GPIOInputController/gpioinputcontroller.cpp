#include "gpioinputcontroller.h"

GPIOInputController::GPIOInputController(ControllerManager* manager, QString id, QObject *parent) : DigitalInputControllerBase (manager, id, parent)
{
    connect(&m_reader, &GPIOReader::stateChanged, this, &GPIOInputController::onStateChanged);
    connect(&m_reader, &GPIOReader::error, this, &GPIOInputController::onError);
}

void GPIOInputController::init() {
    iDebug() << Q_FUNC_INFO;

    DigitalInputControllerBase::init();

    int pinBase = m_config->getInt(this, "mcp.pinBase", 64);
    int addr = m_config->getInt(this, "mcp.addr", 0x20);

    iDebug() << "MCP init" << pinBase << addr;

    m_reader.init(inputCount(), addr, pinBase);
}

void GPIOInputController::start() {
    iDebug() << Q_FUNC_INFO;

    m_reader.start();
}

quint8 GPIOInputController::inputCount() {
    return MCP23017_INPUT_COUNT;
}

void GPIOInputController::onError(QString desc) {
    iWarning() << Q_FUNC_INFO << desc;
}

void GPIOInputController::onStateChanged(quint8 index, bool state) {
    Q_ASSERT(index < inputCount());
    m_valueMappings.at(index)->updateValue(state);
}
