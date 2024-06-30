#ifndef GPIOREADERBASE_H
#define GPIOREADERBASE_H

#include <QObject>
#include <QThread>
#include <QBitArray>

#include "sharedlib.h"

class SHARED_LIB_EXPORT GPIOReaderBase : public QThread
{
    Q_OBJECT
public:
    explicit GPIOReaderBase(int inputCount = 0, QObject *parent = nullptr);

    void enableDebug();

protected:
    quint8 m_inputCount = 0;
    QBitArray* m_states;

    bool m_enableDebug = false;

signals:
    void error(QString desc);
    void stateChanged(quint8 index, bool state);

};

#endif // GPIOREADERBASE_H
