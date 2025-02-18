#ifndef DEVICEDISCOVERYMANAGER_H
#define DEVICEDISCOVERYMANAGER_H

#include <QObject>
#include <QMap>
#include <QTimer>
#include <QDateTime>

#include "sharedlib.h"

#include "device/client/clientdevice.h"
#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"
#include "device/devicediscoverymessage.h"

class SHARED_LIB_EXPORT DeviceDiscoveryManagerBase : public ManagerBase
{
    Q_OBJECT
public:
    explicit DeviceDiscoveryManagerBase(QString serviceId, QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ QString id() override;

    /*virtual*/ void init(LocalConfig* config) override;

    ClientDevice *device();

    void setHealthState(DeviceDiscoveryMessage::DeviceHealthState healthState);

private:
    QString m_serviceId;
    QTimer m_ddTimer;
    ClientDevice* m_device = nullptr;
    CommunicationManagerBase* m_commManager;
    qint64 m_startedTime;
    DeviceDiscoveryMessage::DeviceHealthState m_healthState = DeviceDiscoveryMessage::Healthy;

private slots:
    void startDDBroadcast();
    void stopDDBroadcast();
    void sendDDBroadcast();

public slots:
};

#endif // DEVICEDISCOVERYMANAGER_H
