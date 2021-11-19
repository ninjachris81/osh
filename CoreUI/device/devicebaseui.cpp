#include "devicebaseui.h"

#include "device/knowndevice.h"

#include <QDebug>

DeviceBaseUI::DeviceBaseUI(QObject *parent) : IdentifyableUI(parent)
{
    m_device = static_cast<DeviceBase*>(parent);

    connect(m_device, &DeviceBase::lastPingChanged, this, &DeviceBaseUI::lastPingChanged);
    connect(m_device, &DeviceBase::isOnlineChanged, this, &DeviceBaseUI::isOnlineChanged);
}

QString DeviceBaseUI::fullId() {
    return m_device->fullId();
}

QString DeviceBaseUI::serviceId() {
    return m_device->serviceId();
}

QString DeviceBaseUI::name() {
    if (m_device->inherits(KnownDevice::staticMetaObject.className())) {
        return static_cast<KnownDevice*>(m_device)->name();
    } else {
        return "Unknown device";
    }
}

qint64 DeviceBaseUI::lastPing() {
    return m_device->lastPing();
}

bool DeviceBaseUI::isOnline() {
    return m_device->isOnline();
}
