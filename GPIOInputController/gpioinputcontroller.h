#ifndef GPIOINPUTCONTROLLER_H
#define GPIOINPUTCONTROLLER_H

#include <QObject>

#include "sharedlib.h"

#include "controller/digitalinputcontrollerbase.h"
#include "gpioreaderbase.h"

#define MCP23017_INPUT_COUNT 16

class SHARED_LIB_EXPORT GPIOInputController : public DigitalInputControllerBase
{
Q_OBJECT
public:
    static QLatin1String GPIO_TYPE_PLAIN;
    static QLatin1String GPIO_TYPE_MCP;

    GPIOInputController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ quint8 inputCount() override;

private slots:
    void onStateChanged(quint8 index, bool state);

private:
    ValueManagerBase *m_valueManager;
    quint8 m_inputCount = 0;
    GPIOReaderBase *m_reader = nullptr;

private slots:
    void onError(QString desc);

};

#endif // GPIOINPUTCONTROLLER_H
