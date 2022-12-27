#include "deviceregistry.h"
#include <QUrl>
#include <QDebug>

DeviceRegistry::DeviceRegistry(QObject *parent)
    : QObject{parent}
{

}

QString DeviceRegistry::registerDevice(QString id) {
    qDebug() << Q_FUNC_INFO << id;

    if (!m_deviceMap.contains(id)) {
        DeviceRegistryEntry dev;
        m_deviceMap.insert(id, dev);
    } else {
        qWarning() << "Device already exists" << id;
    }
    return id;
}

void DeviceRegistry::addDeviceInfo(QString id, Device::DeviceInfo deviceInfo) {
    qDebug() << Q_FUNC_INFO << id;

    if (m_deviceMap.contains(id)) {
        DeviceRegistryEntry entry = m_deviceMap.value(id);
        entry.deviceInfo = deviceInfo;
        m_deviceMap.insert(id, entry);
    } else {
        qWarning() << "Device not found" << id;
    }
}

void DeviceRegistry::addDeviceServiceInfo(QString id, QList<Device::DeviceServiceInfo> deviceServiceInfo) {
    qDebug() << Q_FUNC_INFO << id;

    if (m_deviceMap.contains(id)) {
        DeviceRegistryEntry entry = m_deviceMap.value(id);

        QListIterator it(deviceServiceInfo);

        while(it.hasNext()) {
            Device::DeviceServiceInfo info = it.next();
            DeviceServiceId serviceId = getDeviceServiceId(info.deviceNamespace);
            entry.deviceServiceInfo.insert(serviceId, info);
        }
        m_deviceMap.insert(id, entry);
    } else {
        qWarning() << "Device not found" << id;
    }
}

void DeviceRegistry::addProfileTokens(QString id, QStringList profileTokens) {
    qDebug() << Q_FUNC_INFO << id;

    if (m_deviceMap.contains(id)) {
        DeviceRegistryEntry entry = m_deviceMap.value(id);
        entry.profileTokens = profileTokens;
        m_deviceMap.insert(id, entry);
    } else {
        qWarning() << "Device not found" << id;
    }
}

QString DeviceRegistry::getServiceUrl(QString id, DeviceServiceId deviceServiceId) {
    return m_deviceMap.value(id).deviceServiceInfo.value(deviceServiceId).deviceXAddr;
}

QStringList DeviceRegistry::getProfileTokens(QString id) {
    return m_deviceMap.value(id).profileTokens;
}

QString DeviceRegistry::extractId(QString fullUrl) {
    QUrl url(fullUrl);
    return url.host();
}

DeviceRegistry::DeviceServiceId DeviceRegistry::getDeviceServiceId(QString deviceNamespace) {
    if (deviceNamespace.endsWith("/device/wsdl")) return DeviceServiceId::DEVICE_SERVICE;
    if (deviceNamespace.endsWith("/analytics/wsdl")) return DeviceServiceId::ANALYTICS_SERVICE;
    if (deviceNamespace.endsWith("/events/wsdl")) return DeviceServiceId::EVENT_SERVICE;
    if (deviceNamespace.endsWith("/deviceIO/wsdl")) return DeviceServiceId::DEVICEIO_SERVICE;
    if (deviceNamespace.endsWith("/imaging/wsdl")) return DeviceServiceId::IMAGING_SERVICE;
    if (deviceNamespace.endsWith("/media/wsdl")) return DeviceServiceId::MEDIA_SERVICE;
    if (deviceNamespace.endsWith("/ptz/wsdl")) return DeviceServiceId::PTZ_SERVICE;
    if (deviceNamespace.endsWith("/media/wsdl")) return DeviceServiceId::MEDIA_SERVICE;

    qWarning() << "Unknown device namespace" << deviceNamespace;

    return DeviceServiceId::UNKNOWN;
}
