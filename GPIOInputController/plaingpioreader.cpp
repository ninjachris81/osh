#include "plaingpioreader.h"
#include <QDebug>


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
    int returnCode = wiringPiSetup();
    if (returnCode != 0) {
        qWarning() << "Setup returned" << returnCode;
    }
    Q_ASSERT(returnCode == 0);
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
    int m_countMap[m_inputCount];

    while(true) {
        memset(m_countMap, 0, m_inputCount * sizeof(int));

        for (int c = 0;c<GPIO_READ_COUNT;c++) {
            for (quint8 i=0;i<m_inputCount;i++) {
                int pin = m_pinList.at(i);

#ifdef __linux__
                bool state = digitalRead(pin) == LOW;
#else
                Q_UNUSED(pin)
                bool state = false;
#endif

                if (state) {
                    m_countMap[i]++;
                }
            }
            QThread::msleep(1);
        }

        for (quint8 i=0;i<m_inputCount;i++) {
            bool state = m_countMap[i] == GPIO_READ_COUNT;

            if (m_enableDebug) {
                qDebug() << i << m_countMap[i] << "/" << GPIO_READ_COUNT;
            }

            if (m_firstRun || state != m_states->at(i)) {
                m_states->setBit(i, state);
                Q_EMIT(stateChanged(i, state));
            }
        }

        m_firstRun = false;

        QThread::msleep(100);
    }
}

void PlainGPIOReader::close() {
}
