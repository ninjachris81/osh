#pragma once

#include <QObject>

#include "sharedlib.h"

#include "controller/digitalinputcontrollerbase.h"
#include "value/valuemanagerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "serialportclient.h"

class SHARED_LIB_EXPORT RS232InputController : public DigitalInputControllerBase
{
    Q_OBJECT
public:
    explicit RS232InputController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ quint8 inputCount() override;

protected slots:
    void onSerialConnected();
    void onSerialDisconnected();
    void onSerialDataReceived(QByteArray data);

private:
    ValueManagerBase *m_valueManager;
    ClientSystemWarningsManager *m_clientSystemWarningsManager;
    quint8 m_inputCount = 0;

    SerialPortClient *m_serialClient = nullptr;
    qint64 m_lastMessage = 0;

signals:
};

