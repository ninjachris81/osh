#ifndef CLIENTDEVICEMANAGER_H
#define CLIENTDEVICEMANAGER_H

#include <QObject>
#include <QTimer>

#include "manager/managerbase.h"
#include "device/devicediscoverymanagerbase.h"

class ClientDeviceDiscoveryManager : public DeviceDiscoveryManagerBase
{
    Q_OBJECT
public:
    explicit ClientDeviceDiscoveryManager(QObject *parent = nullptr);

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

signals:

public slots:
};

#endif // CLIENTDEVICEMANAGER_H
