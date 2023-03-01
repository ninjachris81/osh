#include "managerbase.h"

#include "device/devicediscoverymanagerbase.h"
#include "manager/managerregistration.h"


ManagerBase::ManagerBase(QObject *parent) : QObject(parent), Identifyable("")
{

}

void ManagerBase::setManagerRegistration(ManagerRegistration* managerRegistration) {
    this->m_managerRegistration = managerRegistration;
}

void ManagerBase::setInitialized() {
    m_isInitialized = true;
}


ManagerRegistration* ManagerBase::managerRegistration() {
    return m_managerRegistration;
}

QString ManagerBase::deviceId() {
    DeviceDiscoveryManagerBase* deviceDiscoveryManager = getManager<DeviceDiscoveryManagerBase>(DeviceDiscoveryManagerBase::MANAGER_ID);
    if (deviceDiscoveryManager != nullptr) {
        return deviceDiscoveryManager->device()->id();
    } else {
        return "";
    }
}
