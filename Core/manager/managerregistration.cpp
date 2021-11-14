#include "managerregistration.h"

#include <QDebug>

#include "manager/managerbase.h"

ManagerRegistration::ManagerRegistration(INSTANCE_ROLE instanceRole, QObject *parent) : QObject(parent), m_instanceRole(instanceRole)
{

}

void ManagerRegistration::registerManager(ManagerBase* manager) {
    qDebug() << Q_FUNC_INFO << manager->getName();

    Q_ASSERT(!m_managers.contains(manager->getName()));
    manager->setManagerRegistration(this);
    m_managers.insert(manager->getName(), manager);
}

ManagerBase* ManagerRegistration::getManager(QString name) {
    if (!m_managers.contains(name)) {
        qWarning() << "Unknown manager" << name;
        return nullptr;
    }
    return m_managers.value(name);
}


void ManagerRegistration::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ManagerBase*> it(m_managers);

    while (it.hasNext()) {
        it.next();

        it.value()->init(config);
    }

    qDebug() << "Post init";

    it.toFront();

    while (it.hasNext()) {
        it.next();

        it.value()->postInit();
    }
}

QStringList ManagerRegistration::managerNames() {
    return m_managers.keys();
}

ManagerRegistration::INSTANCE_ROLE ManagerRegistration::instanceRole() {
    return m_instanceRole;
}
