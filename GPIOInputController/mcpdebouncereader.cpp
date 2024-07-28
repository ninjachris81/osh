#include "mcpdebouncereader.h"

#include <QDebug>

MCPDebounceReader* MCPDebounceReader::m_instance = nullptr;

MCPDebounceReader::MCPDebounceReader(quint8 inputCount, int addr, int pinBase, QObject *parent) : GPIOReaderBase(inputCount, parent),
  m_pinBase(pinBase), m_addr(addr)
{
    m_instance = this;
}

void MCPDebounceReader::run() {
    if (open()) {
        readStates();
        close();
    } else {
        Q_EMIT(error("Failed to open i2c"));
    }
}

void MCPDebounceReader::onInterrupt0() {
    qDebug() << Q_FUNC_INFO;
    m_instance->toggleState(0);
}

void MCPDebounceReader::onInterrupt1() {
    qDebug() << Q_FUNC_INFO;
    m_instance->toggleState(1);
}

void MCPDebounceReader::onInterrupt2() {
    qDebug() << Q_FUNC_INFO;
    m_instance->toggleState(2);
}

void MCPDebounceReader::onInterrupt3() {
    qDebug() << Q_FUNC_INFO;
    m_instance->toggleState(3);
}

void MCPDebounceReader::onInterrupt4() {
    qDebug() << Q_FUNC_INFO;
    m_instance->toggleState(4);
}

void MCPDebounceReader::onInterrupt5() {
    qDebug() << Q_FUNC_INFO;
    m_instance->toggleState(5);
}

void MCPDebounceReader::onInterrupt6() {
    qDebug() << Q_FUNC_INFO;
    m_instance->toggleState(6);
}

void MCPDebounceReader::onInterrupt7() {
    qDebug() << Q_FUNC_INFO;
    m_instance->toggleState(7);
}

bool MCPDebounceReader::open() {
#ifdef __linux__
    int returnCode = wiringPiSetup();
    if (returnCode != 0) {
        qWarning() << "Setup returned" << returnCode;
    }
    Q_ASSERT(returnCode == 0);
    qDebug() << "Setup complete";

    returnCode = mcp23017Setup(m_pinBase, m_addr);
    if (returnCode != TRUE) {
        qWarning() << "Setup returned" << returnCode;
    }
    Q_ASSERT(returnCode == TRUE);
    qDebug() << "MCP Setup complete";
#endif

    m_states = new QBitArray(m_inputCount);

    // setup pins
    for (quint8 i=0;i<m_inputCount;i++) {
#ifdef __linux__
        switch(i) {
        case 0:
            wiringPiISR(i, INT_EDGE_BOTH, &MCPDebounceReader::onInterrupt0);
            break,
        case 1:
            wiringPiISR(i, INT_EDGE_BOTH, &MCPDebounceReader::onInterrupt1);
            break,
        case 2:
            wiringPiISR(i, INT_EDGE_BOTH, &MCPDebounceReader::onInterrupt2);
            break,
        case 3:
            wiringPiISR(i, INT_EDGE_BOTH, &MCPDebounceReader::onInterrupt3);
            break,
        case 4:
            wiringPiISR(i, INT_EDGE_BOTH, &MCPDebounceReader::onInterrupt4);
            break,
        case 5:
            wiringPiISR(i, INT_EDGE_BOTH, &MCPDebounceReader::onInterrupt5);
            break,
        case 6:
            wiringPiISR(i, INT_EDGE_BOTH, &MCPDebounceReader::onInterrupt6);
            break,
        case 7:
            wiringPiISR(i, INT_EDGE_BOTH, &MCPDebounceReader::onInterrupt7);
            break,
        }
#endif
    }

    return true;
}

void MCPDebounceReader::readStates() {
    while(true) {
        QThread::msleep(1);
    }
}

void MCPDebounceReader::close() {
}

void MCPDebounceReader::toggleState(uint8_t index) {
    qDebug() << Q_FUNC_INFO << index;

    m_states->setBit(index, !m_states->at(index));
    Q_EMIT(stateChanged(index, m_states->at(index)));

}
