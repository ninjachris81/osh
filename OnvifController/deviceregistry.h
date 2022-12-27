#ifndef DEVICEREGISTRY_H
#define DEVICEREGISTRY_H

#include <QObject>
#include <QMap>
#include "onvif/device.h"

#include "shared/constants.h"
#include "sharedlib.h"

class SHARED_LIB_EXPORT DeviceRegistry : public QObject
{
    Q_OBJECT
public:
    enum DeviceServiceId {
        UNKNOWN = ENUM_UNKNOWN,
        DEVICE_SERVICE,
        ANALYTICS_SERVICE,
        EVENT_SERVICE,
        DEVICEIO_SERVICE,
        IMAGING_SERVICE,
        MEDIA_SERVICE,
        PTZ_SERVICE
    };

    struct DeviceRegistryEntry {
        Device::DeviceInfo deviceInfo;
        QMap<DeviceServiceId, Device::DeviceServiceInfo> deviceServiceInfo;
        QStringList profileTokens;
    };


    explicit DeviceRegistry(QObject *parent = nullptr);

    QString registerDevice(QString id);

    void addDeviceInfo(QString id, Device::DeviceInfo deviceInfo);
    void addDeviceServiceInfo(QString id, QList<Device::DeviceServiceInfo> deviceServiceInfo);
    void addProfileTokens(QString id, QStringList profileTokens);

    QString getServiceUrl(QString id, DeviceServiceId deviceServiceId);
    QStringList getProfileTokens(QString id);

    static QString extractId(QString fullUrl);
    static DeviceServiceId getDeviceServiceId(QString deviceNamespace);

private:
    QMap<QString, DeviceRegistryEntry> m_deviceMap;


signals:

};

#endif // DEVICEREGISTRY_H
