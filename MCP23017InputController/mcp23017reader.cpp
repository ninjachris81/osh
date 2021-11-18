#include "mcp23017reader.h"

MCP23017Reader::MCP23017Reader(QObject *parent) : QThread(parent)
{

}

void MCP23017Reader::init(quint8 inputCount, int bus, int addr) {
    m_inputCount = inputCount;
    m_bus = bus;
    m_addr = addr;
}

void MCP23017Reader::run() {
    if (open()) {
        readStates();
        close();
    } else {
        Q_EMIT(error("Failed to open i2c"));
    }
}

bool MCP23017Reader::open() {
    if (m_mcp != nullptr) {
        close();
        delete m_mcp;
    }

    m_mcp = new MCP23017(m_bus, m_addr);

    if (m_mcp->openI2C()) {
        m_states = new QBitArray(m_inputCount);

        // setup pins
        for (quint8 i=0;i<m_inputCount;i++) {
            m_mcp->pinMode(i, INPUT);
            m_mcp->pullUp(i, HIGH);  // turn on a 100K pullup internally
        }

        return true;
    } else {
        return false;
    }
}

void MCP23017Reader::readStates() {
    while(true) {
        for (quint8 i=0;i<m_inputCount;i++) {
            bool state = m_mcp->digitalRead(i);

            if (firstRun || state != m_states->at(i)) {
                m_states->setBit(i, state);
                Q_EMIT(stateChanged(i, state));
            }
        }

        firstRun = false;

        QThread::sleep(100);
    }
}

void MCP23017Reader::close() {
    m_mcp->closeI2C();
    delete m_mcp;
}
