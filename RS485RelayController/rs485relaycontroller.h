#ifndef KMTRONICRELAYCONTROLLER_H
#define KMTRONICRELAYCONTROLLER_H

#include <QObject>
#include <QTimer>

#include "controller/relaycontrollerbase.h"
#include "serialportclient.h"
#include "warn/client/clientsystemwarningsmanager.h"

#define MODBUS_HEADER_LENGTH 3
#define MODBUS_CRC_LENTH 2

#define SERIAL_READ_TIMEOUT_MS 2000

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
    void onSerialConnected();
    void onSerialDisconnected();
    void onSerialDataReceived(QByteArray data);

    void retrieveStatus();

private:
    ClientSystemWarningsManager* m_warnManager;
    QTimer m_statusTimer;
    SerialPortClient* m_serialClient;
    uint8_t m_slaveId = 1;
    uint8_t m_expectedDatagramSize;

};

#endif // KMTRONICRELAYCONTROLLER_H
