#include "knowndevice.h"

KnownDevice::KnownDevice(QString id, QString serviceId, QString name, QObject *parent) : DeviceBase(id, serviceId, parent), m_name(name)
{

}

QString KnownDevice::name() {
    return m_name;
}
