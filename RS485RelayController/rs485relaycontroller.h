#ifndef RS485RELAYCONTROLLER_H
#define RS485RELAYCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QModbusRtuSerialMaster>

#include "sharedlib.h"

#include "controller/relaycontrollerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"

class SHARED_LIB_EXPORT RS485RelayController : public RelayControllerBase
{
Q_OBJECT

public:
    enum RELAY_STATUS {
        INIT,
        RETRIEVING_STATUS,
        STATUS_RECEIVED,
        STATUS_ERROR
    } m_currentStatus = INIT;

    enum RELAY_MODEL {
        RS485_SERIAL_32PORT,
        RS485_SERIAL_8PORT
    } m_model;

    RS485RelayController(ControllerManager* manager, QString id, RELAY_MODEL model, QObject *parent = nullptr);
    ~RS485RelayController();

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void switchStatus(quint8 relayIndex, bool status) override;

    static quint8 getRelayCount(RELAY_MODEL model);

    void setSerialRelayStatus(RELAY_STATUS status);

protected slots:
    void onStateChanged();
    void onErrorOccurred();
    void onDataReceived();

    void retrieveStatus();

private:
    QMutex m_Mutex;
    ValueManagerBase *m_valueManager;
    ClientSystemWarningsManager* m_warnManager;
    QModbusRtuSerialMaster m_modbusClient;
    QTimer m_statusTimer;
    int m_slaveId = 1;
    quint8 m_errorCount = 0;

};

#endif // RS485RELAYCONTROLLER_H
