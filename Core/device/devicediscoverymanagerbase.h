#ifndef DEVICEDISCOVERYMANAGER_H
#define DEVICEDISCOVERYMANAGER_H

#include <QObject>
#include <QMap>
#include <QTimer>
#include <QDateTime>

#include "device/client/clientdevice.h"
#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"

class DeviceDiscoveryManagerBase : public ManagerBase
{
    Q_OBJECT
public:
    explicit DeviceDiscoveryManagerBase(QString serviceId, QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ QString id() override;

    /*virtual*/ void init(LocalConfig* config) override;

    ClientDevice *device();

private:
    QString m_serviceId;
    QTimer m_ddTimer;
    ClientDevice* m_device = nullptr;
    CommunicationManagerBase* m_commManager;
    qint64 m_startedTime;

private slots:
    void startDDBroadcast();
    void stopDDBroadcast();
    void sendDDBroadcast();

public slots:
};

#endif // DEVICEDISCOVERYMANAGER_H
