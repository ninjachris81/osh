#include "mcp23017inputcontroller.h"

MCP23017InputController::MCP23017InputController(ControllerManager* manager, QString id, QObject *parent) : DigitalInputControllerBase (manager, id, parent)
{
    connect(&m_reader, &MCP23017Reader::stateChanged, this, &MCP23017InputController::onStateChanged);
    connect(&m_reader, &MCP23017Reader::error, this, &MCP23017InputController::onError);
}

void MCP23017InputController::init() {
    iDebug() << Q_FUNC_INFO;

    DigitalInputControllerBase::init();

    int pinBase = m_config->getInt(this, "mcp.pinBase", 64);
    int addr = m_config->getInt(this, "mcp.addr", 0x20);

    iDebug() << "MCP init" << pinBase << addr;

    m_reader.init(inputCount(), pinBase, addr);
    m_reader.start();
}

quint8 MCP23017InputController::inputCount() {
    return MCP23017_INPUT_COUNT;
}

void MCP23017InputController::onError(QString desc) {
    iWarning() << Q_FUNC_INFO << desc;
}

void MCP23017InputController::onStateChanged(quint8 index, bool state) {
    m_valueMappings.at(index)->updateValue(state);
}
