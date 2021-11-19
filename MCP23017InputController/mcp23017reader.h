#ifndef MCP23017READER_H
#define MCP23017READER_H

#include <QObject>
#include <QThread>
#include <QBitArray>

#ifdef __linux__
#include <wiringPi.h>
#include <mcp23017.h>
#endif

class MCP23017Reader : public QThread
{
    Q_OBJECT
public:
    explicit MCP23017Reader(QObject *parent = nullptr);

    void init(quint8 inputCount, int bus, int addr);

    /*virtual*/ void run() override;

private:
    quint8 m_inputCount = 0;
    int m_bus = 0;
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

#endif // MCP23017READER_H
