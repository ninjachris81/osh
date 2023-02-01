#ifndef CLIENTDEVICEMANAGER_H
#define CLIENTDEVICEMANAGER_H

#include <QObject>
#include <QTimer>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "device/devicediscoverymanagerbase.h"

class SHARED_LIB_EXPORT ClientDeviceDiscoveryManager : public DeviceDiscoveryManagerBase
{
    Q_OBJECT
public:
    explicit ClientDeviceDiscoveryManager(QString serviceId, QObject *parent = nullptr);

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

signals:

public slots:
};

#endif // CLIENTDEVICEMANAGER_H
