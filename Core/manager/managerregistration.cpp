#include "managerregistration.h"

#include <QDebug>
#include <QLoggingCategory>

#include "manager/managerbase.h"
#include "log/logmanager.h"

ManagerRegistration::ManagerRegistration(INSTANCE_ROLE instanceRole, QObject *parent) : QObject(parent), Identifyable ("ManagerRegistration"), m_instanceRole(instanceRole)
{

}

LogCat::LOGCAT ManagerRegistration::logCat() {
    return LogCat::COMMON;
}

void ManagerRegistration::registerManager(ManagerBase* manager) {
    iDebug() << Q_FUNC_INFO << manager->id();

    Q_ASSERT(!m_managers.contains(manager->id()));
    manager->setManagerRegistration(this);
    m_managers.insert(manager->id(), manager);
}

ManagerBase* ManagerRegistration::getManager(QString name) {
    if (!m_managers.contains(name)) {
        iWarning() << "Unknown manager" << name;
        return nullptr;
    }
    return m_managers.value(name);
}


void ManagerRegistration::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    QMapIterator<QString, ManagerBase*> it(m_managers);

    if (m_managers.contains(LogManager::MANAGER_ID)) {
        LogManager* logManager = static_cast<LogManager*>(getManager(LogManager::MANAGER_ID));

        while (it.hasNext()) {
            it.next();

            logManager->registerManager(it.value());
        }

        iDebug() << "Priority init log manager";
        logManager->init(config);           // init this one first
    } else {
        iWarning() << "No log manager defined";
    }

    // first stage: init priority managers
    it.toFront();
    while (it.hasNext()) {
        it.next();

        if (it.value()->isPriorityManager() && it.key() != LogManager::MANAGER_ID) {
            it.value()->init(config);
        }
    }

    // 2nd stage: init non-priority managers
    it.toFront();
    while (it.hasNext()) {
        it.next();

        if (!it.value()->isPriorityManager() && it.key() != LogManager::MANAGER_ID) {
            it.value()->init(config);
        }
    }

    // last stage: post init
    iDebug() << "Post init";

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
