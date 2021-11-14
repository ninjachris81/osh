#ifndef DEVICEDISCOVERMANAGERSERVER_H
#define DEVICEDISCOVERMANAGERSERVER_H

#include <QObject>

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif


#include "device/devicediscoverymanagerbase.h"
#include "communication/messagebase.h"
#include "device/devicediscoverymodelbridge.h"

class DeviceDiscoveryManagerServer : public DeviceDiscoveryManagerBase
{
    Q_OBJECT
public:
    explicit DeviceDiscoveryManagerServer(QObject *parent = nullptr);

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

protected:
    DeviceDiscoveryModelBridge* m_modelBridge;

signals:

public slots:
};

#endif // DEVICEDISCOVERMANAGERSERVER_H
