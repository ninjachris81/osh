#include "doorunlock_controller.h"

#include <QDebug>

#include "controller/controllermanager.h"
#include "shared/controllercmdtypes_qt.h"
#include "controller/controllermessage.h"

DoorUnlockController::DoorUnlockController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent) {
}

void DoorUnlockController::init() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);
}

void DoorUnlockController::start() {
    iDebug() << Q_FUNC_INFO;
}

void DoorUnlockController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}
