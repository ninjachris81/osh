#include "managerbase.h"

#include "manager/managerregistration.h"


ManagerBase::ManagerBase(QObject *parent) : QObject(parent)
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
