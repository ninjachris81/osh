#include "knowndevice.h"

KnownDevice::KnownDevice(QString id, QString location, QObject *parent) : DeviceBase(id, parent), m_location(location)
{

}

QString KnownDevice::location() {
    return m_location;
}
