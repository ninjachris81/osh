#ifndef PLAINGPIOREADER_H
#define PLAINGPIOREADER_H

#include <QObject>
#include <QThread>

#include "sharedlib.h"
#include "gpioreaderbase.h"

#ifdef __linux__
    #include <wiringPi.h>
#endif

class PlainGPIOReader : public GPIOReaderBase
{
    Q_OBJECT
public:
    explicit PlainGPIOReader(QList<int> pinList, QObject *parent = nullptr);

    void run() override;

    bool open();
    void readStates();
    void close();

private:
    QList<int> m_pinList;
    bool firstRun = true;

signals:

};

#endif // PLAINGPIOREADER_H
