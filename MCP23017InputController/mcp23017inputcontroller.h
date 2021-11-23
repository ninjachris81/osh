#ifndef MCP23017INPUTCONTROLLER_H
#define MCP23017INPUTCONTROLLER_H

#include <QObject>
#include "controller/digitalinputcontrollerbase.h"
#include "mcp23017reader.h"

#define MCP23017_INPUT_COUNT 16

class MCP23017InputController : public DigitalInputControllerBase
{
Q_OBJECT
public:
    MCP23017InputController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ quint8 inputCount() override;

private slots:
    void onStateChanged(quint8 index, bool state);

private:
    MCP23017Reader m_reader;

private slots:
    void onError(QString desc);

};

#endif // MCP23017INPUTCONTROLLER_H
