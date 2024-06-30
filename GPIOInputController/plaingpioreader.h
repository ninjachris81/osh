#ifndef PLAINGPIOREADER_H
#define PLAINGPIOREADER_H

#include <QObject>
#include <QThread>
#include <QMap>

#include "sharedlib.h"
#include "gpioreaderbase.h"

#ifdef __linux__
    #include <wiringPi.h>
#endif

#define GPIO_READ_COUNT 10

class SHARED_LIB_EXPORT PlainGPIOReader : public GPIOReaderBase
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
    bool m_firstRun = true;

signals:

};

#endif // PLAINGPIOREADER_H
