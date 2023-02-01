#ifndef KMTRONICRELAYCONTROLLER_H
#define KMTRONICRELAYCONTROLLER_H

#include <QObject>
#include <QTimer>

#include "sharedlib.h"

#include "controller/relaycontrollerbase.h"
#include "serialportclient.h"
#include "warn/client/clientsystemwarningsmanager.h"

#define SERIAL_READ_TIMEOUT_MS 2000

class SHARED_LIB_EXPORT KMTronicRelayController : public RelayControllerBase
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
        USB_SERIAL_8PORT
    } m_model;

    KMTronicRelayController(ControllerManager* manager, QString id, RELAY_MODEL model, quint8 relayCount, QObject *parent = nullptr);

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

};

#endif // KMTRONICRELAYCONTROLLER_H
