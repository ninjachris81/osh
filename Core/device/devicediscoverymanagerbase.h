#ifndef DEVICEDISCOVERYMANAGER_H
#define DEVICEDISCOVERYMANAGER_H

#include <QObject>
#include <QMap>
#include <QTimer>

#include "device/client/clientdevice.h"
#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"

class DeviceDiscoveryManagerBase : public ManagerBase
{
    Q_OBJECT
public:
    explicit DeviceDiscoveryManagerBase(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ QString getName();

    /*virtual*/ void init(LocalConfig* config);

    ClientDevice *device();

private:
    QTimer m_ddTimer;
    ClientDevice* m_device;
    CommunicationManagerBase* m_commManager;

private slots:
    void startDDBroadcast();
    void stopDDBroadcast();
    void sendDDBroadcast();

public slots:
};

#endif // DEVICEDISCOVERYMANAGER_H
