#include "doorunlock_controller.h"

#include <QDebug>
#include <QTimer>

#include "controller/controllermanager.h"
#include "shared/controllercmdtypes_qt.h"
#include "controller/controllermessage.h"

#include "helpers.h"

#ifdef __linux__
    #include <wiringPi.h>
#endif

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

    REQUIRE_MANAGER_X(m_manager, ClientValueManager);
    m_valueManager = m_manager->getManager<ClientValueManager>(ClientValueManager::MANAGER_ID);

    relayEnableDurationMs = m_config->getInt(this, "relayEnableDuration", 3000);
    m_relayPin = m_config->getInt(this, "relayPin", 0);     // if not specified, using external relay (not safe!!!)
    initRelay();

    Helpers::safeConnect(m_doorUnlockManager, &DoorUnlockManager::unlockDoor, this, &DoorUnlockController::onUnlockDoor, SIGNAL(unlockDoor(QString)), SLOT(onUnlockDoor(QString)));
}

void DoorUnlockController::start() {
    iDebug() << Q_FUNC_INFO;
}

void DoorUnlockController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void DoorUnlockController::bindActors(DoorActor* doorActor, DigitalActor* relay) {
    iDebug() << Q_FUNC_INFO << relay->id();
    this->m_door = doorActor;
    this->m_relay = relay;
}

void DoorUnlockController::onUnlockDoor(QString doorId) {
    QMutexLocker locker(&unlockingMutex);

    if (this->m_door->fullId() == doorId) {
        iDebug() << Q_FUNC_INFO << doorId;
        if (m_isUnlocking) {
            iWarning() << "Unlocking already in progress";
            return;
        }

        iDebug() << "Unlock door" << doorId;
        m_isUnlocking = true;

        m_actorManager->publishCmd(m_relay, actor::ACTOR_CMD_ON, true);
        m_valueManager->updateAndPublishValue(m_door, true);
        enableRelay(true);

        QTimer::singleShot(relayEnableDurationMs, this, [this] () {
            m_actorManager->publishCmd(m_relay, actor::ACTOR_CMD_OFF, false);
            m_valueManager->updateAndPublishValue(m_door, false);
            enableRelay(false);
            iDebug() << "Unlock door finished" << m_door->id();
            m_isUnlocking = false;
        });
    } else {
        iInfo() << "Event is for different door" << doorId;
    }
}

void DoorUnlockController::initRelay() {
    iInfo() << Q_FUNC_INFO;

    if (m_relayPin > 0) {
#ifdef __linux__
        wiringPiSetup();
        pinMode (m_relayPin, OUTPUT) ;
        pullUpDnControl (m_relayPin, PUD_UP);
#else
        iInfo() << "Simulating relay init";
#endif
    }
}

void DoorUnlockController::enableRelay(bool enable) {
    iInfo() << Q_FUNC_INFO << enable;

    if (m_relayPin > 0) {
#ifdef __linux__
        digitalWrite(m_relayPin, enable ? HIGH : LOW);
#else
        iInfo() << "Simulating relay" << enable;
#endif
    }
}
