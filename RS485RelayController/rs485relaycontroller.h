#ifndef KMTRONICRELAYCONTROLLER_H
#define KMTRONICRELAYCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QModbusRtuSerialMaster>

#include "controller/relaycontrollerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"

class RS485RelayController : public RelayControllerBase
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
        RS485_SERIAL_32PORT
    } m_model;

    RS485RelayController(ControllerManager* manager, QString id, RELAY_MODEL model, quint8 relayCount, QObject *parent = nullptr);

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
    ClientSystemWarningsManager* m_warnManager;
    QModbusRtuSerialMaster m_modbusClient;
    QTimer m_statusTimer;
    int m_slaveId = 1;

};

#endif // KMTRONICRELAYCONTROLLER_H
