#include "plaingpioreader.h"

PlainGPIOReader::PlainGPIOReader(QList<int> pinList, QObject *parent)
    : GPIOReaderBase(pinList.count(), parent), m_pinList(pinList)
{
}

void PlainGPIOReader::run() {
    if (open()) {
        readStates();
        close();
    } else {
        Q_EMIT(error("Failed to open i2c"));
    }
}

bool PlainGPIOReader::open() {
#ifdef __linux__
    wiringPiSetup();
#endif

    m_states = new QBitArray(m_inputCount);

    // setup pins
    for (quint8 i=0;i<m_inputCount;i++) {
        int pin = m_pinList.at(i);

#ifdef __linux__
        pinMode (pin, INPUT) ;
        pullUpDnControl (pin, PUD_UP);
#else
        Q_UNUSED(pin)
#endif
    }

    return true;
}

void PlainGPIOReader::readStates() {
    while(true) {
        for (quint8 i=0;i<m_inputCount;i++) {
            int pin = m_pinList.at(i);

#ifdef __linux__
            bool state = digitalRead(pin) == LOW;
#else
            Q_UNUSED(pin)
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

void PlainGPIOReader::close() {
}