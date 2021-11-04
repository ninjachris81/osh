#include "devicebase.h"

#include <QDateTime>

DeviceBase::DeviceBase(QString id, QObject *parent) : Identifyable(id, parent)
{

}

void DeviceBase::updatePing() {
    this->m_lastPing = QDateTime::currentMSecsSinceEpoch();
}
