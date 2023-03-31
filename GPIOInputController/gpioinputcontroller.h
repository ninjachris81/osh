#ifndef GPIOINPUTCONTROLLER_H
#define GPIOINPUTCONTROLLER_H

#include <QObject>

#include "sharedlib.h"

#include "controller/digitalinputcontrollerbase.h"
#include "gpioreader.h"

#define MCP23017_INPUT_COUNT 16

class SHARED_LIB_EXPORT GPIOInputController : public DigitalInputControllerBase
{
Q_OBJECT
public:
    GPIOInputController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ quint8 inputCount() override;

private slots:
    void onStateChanged(quint8 index, bool state);

private:
    GPIOReader m_reader;

private slots:
    void onError(QString desc);

};

#endif // GPIOINPUTCONTROLLER_H
