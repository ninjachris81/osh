#ifndef GPIOINPUTCONTROLLER_H
#define GPIOINPUTCONTROLLER_H

#include <QObject>

#include "sharedlib.h"

#include "controller/digitalinputcontrollerbase.h"
#include "value/valuemanagerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "gpioreaderbase.h"
#include "i2csanitychecker.h"

#define MCP23017_INPUT_COUNT 16

class SHARED_LIB_EXPORT GPIOInputController : public DigitalInputControllerBase
{
Q_OBJECT
public:
    static QLatin1String GPIO_TYPE_PLAIN;
    static QLatin1String GPIO_TYPE_MCP;
    static QLatin1String GPIO_TYPE_MCP_ISR;

    GPIOInputController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ quint8 inputCount() override;

private slots:
    void onStateChanged(quint8 index, bool state);
    void onI2cNotDetected();

private:
    ValueManagerBase *m_valueManager;
    ClientSystemWarningsManager *m_clientSystemWarningsManager;
    quint8 m_inputCount = 0;
    GPIOReaderBase *m_reader = nullptr;
    I2CSanityChecker m_i2cSanityChecker;

private slots:
    void onError(QString desc);

};

#endif // GPIOINPUTCONTROLLER_H
