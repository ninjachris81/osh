#include "knowndevice.h"

KnownDevice::KnownDevice() : DeviceBase() {

}

KnownDevice::KnownDevice(QString id, QString serviceId, QString name, QObject *parent) : DeviceBase(id, serviceId, parent), m_name(name)
{

}

QString KnownDevice::name() {
    return m_name;
}

void KnownDevice::serialize(QJsonObject &obj) {
    DeviceBase::serialize(obj);
    obj.insert("name", m_name);
}

void KnownDevice::deserialize(QJsonObject obj) {
    DeviceBase::deserialize(obj);
    m_name = obj.value("name").toString();
}
