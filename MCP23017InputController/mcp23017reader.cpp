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
#ifdef __linux__
    mcp23017Setup (bus, addr);
#endif

    m_states = new QBitArray(m_inputCount);

    // setup pins
    for (quint8 i=0;i<m_inputCount;i++) {
#ifdef __linux__
        pinMode (m_bus + i, OUTPUT) ;
        pullUpDnControl ( m_bus + i, PUD_UP);
#endif
    }

    return true;
}

void MCP23017Reader::readStates() {
    while(true) {
        for (quint8 i=0;i<m_inputCount;i++) {
#ifdef __linux__
            bool state = digitalRead(i);
#else
            bool state = false;
#endif

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
}
