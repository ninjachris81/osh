#ifndef DEVICEDISCOVERYMANAGER_H
#define DEVICEDISCOVERYMANAGER_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>
#include <QMap>

#include "manager/managerbase.h"
#include "communication/messagebase.h"
#include "devicebase.h"
#include "knowndevice.h"

class DeviceDiscoveryManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit DeviceDiscoveryManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    DeviceBase* registerUnknownDevice(QString id);

private:
    QMap<QString, DeviceBase*> m_unknownDevices;
    QMap<QString, KnownDevice*> m_knownDevices;

signals:

public slots:
};

#endif // DEVICEDISCOVERYMANAGER_H
