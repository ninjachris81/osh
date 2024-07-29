#include "mcpreader.h"

#include <QDebug>

MCPReader::MCPReader(quint8 inputCount, int addr, int pinBase, int pinOffset, QObject *parent) : GPIOReaderBase(inputCount, parent),
  m_pinBase(pinBase), m_addr(addr), m_pinOffset(pinOffset)
{

}

void MCPReader::run() {
    if (open()) {
        readStates();
        close();
    } else {
        Q_EMIT(error("Failed to open i2c"));
    }
}

bool MCPReader::open() {
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
        pinMode (m_pinOffset + i, INPUT) ;
        pullUpDnControl ( m_pinOffset + i, PUD_UP);
#endif
    }

    return true;
}

void MCPReader::readStates() {
    QString debugStr;

    while(true) {
        debugStr.clear();

        for (quint8 i=0;i<m_inputCount;i++) {
#ifdef __linux__
            bool state = digitalRead(m_pinOffset + i) == LOW;
#else
            bool state = false;
#endif

            if (firstRun || state != m_states->at(i)) {
                m_states->setBit(i, state);
                Q_EMIT(stateChanged(i, state));
            }

            debugStr.append(QString::number(i) + "=" + state + " ");
        }

        if (m_enableDebug) {
            qDebug() << debugStr;
        }

        firstRun = false;

        QThread::msleep(100);
    }
}

void MCPReader::close() {
}
