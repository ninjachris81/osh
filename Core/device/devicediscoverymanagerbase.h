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

    static QLatin1Literal MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ QString id() override;

    /*virtual*/ void init(LocalConfig* config) override;

    ClientDevice *device();

private:
    QTimer m_ddTimer;
    ClientDevice* m_device = nullptr;
    CommunicationManagerBase* m_commManager;

private slots:
    void startDDBroadcast();
    void stopDDBroadcast();
    void sendDDBroadcast();

public slots:
};

#endif // DEVICEDISCOVERYMANAGER_H
