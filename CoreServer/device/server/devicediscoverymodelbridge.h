#ifndef DEVICEDISCOVERYMODELBRIDGE_H
#define DEVICEDISCOVERYMODELBRIDGE_H

#include <QObject>
#include <QTimer>

#include "datamodel/server/datamodelmanager.h"
#include "device/devicediscoverymanagerbase.h"
#include "device/devicediscoverymessage.h"

#include "identifyable.h"

class DeviceDiscoveryModelBridge : public Identifyable
{
    Q_OBJECT
public:
    explicit DeviceDiscoveryModelBridge(DeviceDiscoveryManagerBase *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    void init(LocalConfig *config);

    DeviceBase* registerUnknownDevice(QString id, QString serviceId);

    DeviceBase* handleReceivedMessage(DeviceDiscoveryMessage* msg);

    QMap<QString, DeviceBase*> unknownDevices();

    QMap<QString, KnownDevice*> knownDevices();

private:
    DeviceDiscoveryManagerBase* m_parent;
    QMap<QString, DeviceBase*> m_unknownDevices;
    DatamodelManager* m_datamodelManager;

    QTimer m_onlineCheckTimer;
    qint64 m_onlineCheckTimeout;

signals:
    void unknownDevicesChanged();

private slots:
    void onOnlineCheck();

public slots:
};

#endif // DEVICEDISCOVERYMODELBRIDGE_H
