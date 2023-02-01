#ifndef DEVICE_H
#define DEVICE_H

#include <QString>
#include <QList>

class Device
{
public:
    Device();
    ~Device();

    struct DeviceServiceInfo {
        QString deviceXAddr = "";
        QString deviceNamespace = "";
    };

    struct DeviceInfo {
        QString deviceFirmwareVersion = "";
        QString deviceSerialNumber = "";
        QString deviceHardwareId = "";
        QString deviceManufacturer = "";
    };

    static DeviceInfo getDeviceInformation(QString devServiceURL);
    static void getUsers(QString devServiceURL);

    static QList<DeviceServiceInfo> getServices(QString deviceServiceURL);
};

#endif // DEVICE_H
