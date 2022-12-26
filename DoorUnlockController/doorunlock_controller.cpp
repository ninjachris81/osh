#include "doorunlock_controller.h"

#include <QDebug>
#include <QTimer>

#include "controller/controllermanager.h"
#include "shared/controllercmdtypes_qt.h"
#include "controller/controllermessage.h"

#include "helpers.h"

DoorUnlockController::DoorUnlockController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent) {
}

void DoorUnlockController::init() {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, DoorUnlockManager);
    m_doorUnlockManager = m_manager->getManager<DoorUnlockManager>(DoorUnlockManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ActorManager);
    m_actorManager = m_manager->getManager<ActorManager>(ActorManager::MANAGER_ID);

    Helpers::safeConnect(m_doorUnlockManager, &DoorUnlockManager::unlockDoor, this, &DoorUnlockController::onUnlockDoor, SIGNAL(unlockDoor(QString)), SLOT(onUnlockDoor(QString)));
}

void DoorUnlockController::start() {
    iDebug() << Q_FUNC_INFO;
}

void DoorUnlockController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void DoorUnlockController::bindDoorActor(DoorActor* door, DigitalActor* relay) {
    iDebug() << Q_FUNC_INFO << door->id() << relay->id();
    this->m_door = door;
    this->m_relay = relay;
}

void DoorUnlockController::onUnlockDoor(QString doorId) {
    iDebug() << Q_FUNC_INFO << doorId;

    if (this->m_door->id() == doorId) {
        iDebug() << "Unlock door" << doorId;
        m_actorManager->publishCmd(m_relay, actor::ACTOR_CMD_ON);

        QTimer::singleShot(UNLOCK_ENABLE_DURATION_MS, this, [this] () {
            m_actorManager->publishCmd(m_relay, actor::ACTOR_CMD_OFF);
            iDebug() << "Unlock door finished" << m_door->id();
        });
    }
}
