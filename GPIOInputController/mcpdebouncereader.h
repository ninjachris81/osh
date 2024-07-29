#ifndef MCPDEBOUNCEREADER_H
#define MCPDEBOUNCEREADER_H

#include <QObject>
#include <QThread>

#include "sharedlib.h"
#include "gpioreaderbase.h"

#ifdef __linux__
#include <wiringPi.h>
#include <mcp23017.h>
#endif

class SHARED_LIB_EXPORT MCPDebounceReader : public GPIOReaderBase
{
    Q_OBJECT
public:
    explicit MCPDebounceReader(quint8 inputCount, int addr, int pinBase = 64, int pinOffset = 0, QObject *parent = nullptr);

    /*virtual*/ void run() override;

    static void onInterrupt0();
    static void onInterrupt1();
    static void onInterrupt2();
    static void onInterrupt3();
    static void onInterrupt4();
    static void onInterrupt5();
    static void onInterrupt6();
    static void onInterrupt7();


    static MCPDebounceReader* m_instance;

    void toggleState(uint8_t index);

private:
    int m_pinBase = 0;
    int m_addr = 0;
    int m_pinOffset = 0;

    bool open();
    void readStates();
    void close();

signals:

public slots:
};

#endif // MCPDEBOUNCEREADER_H
