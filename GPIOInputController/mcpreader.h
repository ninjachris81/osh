#ifndef MCPREADER_H
#define MCPREADER_H

#include <QObject>
#include <QThread>

#include "sharedlib.h"
#include "gpioreaderbase.h"

#ifdef __linux__
#include <wiringPi.h>
#include <mcp23017.h>
#endif

class SHARED_LIB_EXPORT MCPReader : public GPIOReaderBase
{
    Q_OBJECT
public:
    explicit MCPReader(quint8 inputCount, int addr, int pinBase = 64, QObject *parent = nullptr);

    /*virtual*/ void run() override;

private:
    int m_pinBase = 0;
    int m_addr = 0;

    bool firstRun = true;

    bool open();
    void readStates();
    void close();

signals:

public slots:
};

#endif // MCPREADER_H