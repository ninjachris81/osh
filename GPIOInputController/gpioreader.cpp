#include "gpioreader.h"

GPIOReader::GPIOReader(QObject *parent) : QThread(parent)
{

}

void GPIOReader::init(quint8 inputCount, int addr, int pinBase) {
    m_inputCount = inputCount;
    m_pinBase = pinBase;
    m_addr = addr;
}

void GPIOReader::run() {
    if (open()) {
        readStates();
        close();
    } else {
        Q_EMIT(error("Failed to open i2c"));
    }
}

bool GPIOReader::open() {
#ifdef __linux__
    wiringPiSetup();
    mcp23017Setup(m_pinBase, m_addr);
#endif

    m_states = new QBitArray(m_inputCount);

    // setup pins
    for (quint8 i=0;i<m_inputCount;i++) {
#ifdef __linux__
        pinMode (m_pinBase + i, INPUT) ;
        pullUpDnControl ( m_pinBase + i, PUD_UP);
#endif
    }

    return true;
}

void GPIOReader::readStates() {
    while(true) {
        for (quint8 i=0;i<m_inputCount;i++) {
#ifdef __linux__
            bool state = digitalRead(m_pinBase + i) == LOW;
#else
            bool state = false;
#endif

            if (firstRun || state != m_states->at(i)) {
                m_states->setBit(i, state);
                Q_EMIT(stateChanged(i, state));
            }
        }

        firstRun = false;

        QThread::msleep(100);
    }
}

void GPIOReader::close() {
}
