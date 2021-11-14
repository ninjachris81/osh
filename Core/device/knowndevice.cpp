#include "knowndevice.h"

KnownDevice::KnownDevice(QString id, QString name, QObject *parent) : DeviceBase(id, parent), m_name(name)
{

}

QString KnownDevice::name() {
    return m_name;
}
