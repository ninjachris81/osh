#ifndef GPIOREADER_H
#define GPIOREADER_H

#include <QObject>
#include <QThread>
#include <QBitArray>

#include "sharedlib.h"

#ifdef __linux__
#include <wiringPi.h>
#include <mcp23017.h>
#endif

class SHARED_LIB_EXPORT GPIOReader : public QThread
{
    Q_OBJECT
public:
    explicit GPIOReader(QObject *parent = nullptr);

    void init(quint8 inputCount, int addr, int pinBase = 64);

    /*virtual*/ void run() override;

private:
    quint8 m_inputCount = 0;
    int m_pinBase = 0;
    int m_addr = 0;

    QBitArray* m_states;
    bool firstRun = true;

    bool open();
    void readStates();
    void close();

signals:
    void error(QString desc);
    void stateChanged(quint8 index, bool state);

public slots:
};

#endif // GPIOREADER_H
