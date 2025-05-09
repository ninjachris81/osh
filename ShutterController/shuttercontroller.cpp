#include "shuttercontroller.h"

#include <QDebug>
#include <QDateTime>

#include "controller/controllermanager.h"
#include "controller/controllermessage.h"
#include "helpers.h"

ShutterController::ShutterController(ControllerManager *manager, ActorManager* actorManager , QString id, QObject *parent) : ControllerBase(manager, id, parent), m_actorManager(actorManager)
{
    m_maintenanceTimer.setInterval(500);
    connect(&m_maintenanceTimer, &QTimer::timeout, this, &ShutterController::onMaintenance);
}

void ShutterController::init() {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);
}


void ShutterController::start() {
    iDebug() << Q_FUNC_INFO;

    initializeShutters();
}

void ShutterController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void ShutterController::initializeShutters() {
    iDebug() << Q_FUNC_INFO;

    // first, initialize all shutters
    for (ShutterActor* actor : m_actorsUp.keys()) {
        actor->updateClosePattern(SHUTTER_CLOSED);      // assume it's closed
        m_valueManager->publishValue(actor);
        insertShutterMovements(actor, actor::ACTOR_CMD_UP, true);
    }

    m_maintenanceTimer.start();
}

void ShutterController::bindActor(ShutterActor *shutterActor, DigitalActor* relayActorUp, DigitalActor* relayActorDown) {
    m_actorsUp.insert(shutterActor, relayActorUp);
    m_actorsDown.insert(shutterActor, relayActorDown);

    Helpers::safeConnect(shutterActor, &ShutterActor::cmdTriggered, this, &ShutterController::onCmdTriggered, SIGNAL(cmdTriggered(actor::ACTOR_CMDS)), SLOT(onCmdTriggered(actor::ACTOR_CMDS)));
}

void ShutterController::onCmdTriggered(actor::ACTOR_CMDS cmd) {
    ShutterActor *shutterActor = qobject_cast<ShutterActor*>(sender());

    switch(cmd) {
    case actor::ACTOR_CMD_STOP:
    case actor::ACTOR_CMD_UP:
    case actor::ACTOR_CMD_DOWN:
        insertShutterMovements(shutterActor, cmd);
        break;
    case actor::ACTOR_CMD_SHUTTER_HALF_CLOSE:
    case actor::ACTOR_CMD_SHUTTER_HALF_OPEN:
    case actor::ACTOR_CMD_SHUTTER_FULL_OPEN:
    case actor::ACTOR_CMD_SHUTTER_TURN_OPEN:
    case actor::ACTOR_CMD_SHUTTER_TURN_CLOSE:
        if (shutterActor->tiltSupport()) {
            insertShutterMovements(shutterActor, cmd);
        } else {
            iWarning() << "Tilt not supported";
        }
        break;
    default:
        iWarning() << "Unsupported cmd" << cmd;
    }
}

void ShutterController::onMaintenance() {
    QMutexLocker locker(&m_activeShutterMovementsMutex);

    QStringList activeShutters;
    QMutableListIterator<ActiveShutterMovement> it(m_activeShutterMovements);
    while(it.hasNext()) {
        ActiveShutterMovement movement = it.next();

        if (activeShutters.contains(movement.shutterActor->fullId())) {
            iDebug() << "Skipping next action of shutter" << movement.shutterActor->fullId();
            continue;
        }

        // else, ok, different shutter, so execute
        activeShutters << movement.shutterActor->fullId();

        if (movement.startedAt == -1) {     // not started, so start it
            m_actorManager->publishCmd(movement.relayActor, actor::ACTOR_CMD_ON);
            movement.startedAt = QDateTime::currentMSecsSinceEpoch();
            it.setValue(movement);
        } else if (QDateTime::currentMSecsSinceEpoch() - movement.startedAt > movement.duration) {      // stop it
            if (movement.isTilt) {
                movement.shutterActor->updateTiltPattern(movement.directionDown ? SHUTTER_TILT_CLOSED : SHUTTER_TILT_OPENED);
            } else {
                movement.shutterActor->updateClosePattern(movement.directionDown ? SHUTTER_CLOSED : SHUTTER_OPENED);
            }

            m_actorManager->publishCmd(movement.relayActor, actor::ACTOR_CMD_OFF);
            it.remove();        // remove the task
        } else if (movement.updatesStatus) {
            // update value
            double elapsedTime = QDateTime::currentMSecsSinceEpoch() - movement.startedAt;
            double duration = movement.duration;
            int percentage = qBound(SHUTTER_STATE_OPENED, (int) ((elapsedTime / duration) * 100), SHUTTER_STATE_CLOSED);

            // border handling
            if (percentage > 95) percentage = SHUTTER_STATE_CLOSED;
            if (percentage < 5) percentage = SHUTTER_STATE_OPENED;

            // invert
            if (!movement.directionDown) {
                percentage = 100 - percentage;
            }

            if (movement.isTilt) {
                movement.shutterActor->updateTiltPattern(percentage);
            } else {
                movement.shutterActor->updateClosePattern(percentage);
            }
            m_valueManager->publishValue(movement.shutterActor);
        }
    }
}

void ShutterController::insertShutterMovements(ShutterActor* shutterActor, actor::ACTOR_CMDS cmd, bool isInit) {
    if (!checkShutterInitMovements(shutterActor, cmd)) {
        iWarning() << "Cannot insert new movement - still initializing";
        return;
    }

    switch(cmd) {
    case actor::ACTOR_CMD_STOP:
        // just make sure both as off
        m_actorManager->publishCmd(m_actorsUp.value(shutterActor), actor::ACTOR_CMD_OFF);
        m_actorManager->publishCmd(m_actorsDown.value(shutterActor), actor::ACTOR_CMD_OFF);
        break;
    case actor::ACTOR_CMD_UP:
        insertShutterMovement(shutterActor, cmd, shutterActor->fullCloseDuration() + shutterActor->fullTiltDuration(), false, true, isInit, false);
        break;
    case actor::ACTOR_CMD_DOWN:
        insertShutterMovement(shutterActor, cmd, shutterActor->fullCloseDuration(), true, true, isInit, false);
        break;
    case actor::ACTOR_CMD_SHUTTER_FULL_OPEN:
        if (shutterActor->checkTiltSupport()) {
            if (shutterActor->closeState() == SHUTTER_OPENED) {
                // first, all down
                insertShutterMovement(shutterActor, cmd, shutterActor->fullCloseDuration(), true, true, isInit, false);
            }

            // then, turn open
            insertShutterMovement(shutterActor, cmd, shutterActor->fullTiltDuration(), false, false, isInit, true);
        } else {
            iWarning() << "Actor does not support tilting";
        }
        break;
    case actor::ACTOR_CMD_SHUTTER_TURN_CLOSE:
        if (shutterActor->checkTiltSupport()) {
            insertShutterMovement(shutterActor, cmd, shutterActor->fullTiltDuration(), true, false, isInit, true);
        } else {
            iWarning() << "Actor does not support tilting";
        }
        break;
    case actor::ACTOR_CMD_SHUTTER_TURN_OPEN:
        if (shutterActor->checkTiltSupport()) {
            insertShutterMovement(shutterActor, cmd, shutterActor->fullTiltDuration(), false, false, isInit, true);
        } else {
            iWarning() << "Actor does not support tilting";
        }
        break;
    case actor::ACTOR_CMD_SHUTTER_HALF_CLOSE:
        if (shutterActor->closeState() == SHUTTER_CLOSED) {
            insertShutterMovement(shutterActor, cmd, shutterActor->fullCloseDuration() / m_halfFactor, false, true, isInit, false);
            if (shutterActor->checkTiltSupport()) {
                insertShutterMovement(shutterActor, cmd, shutterActor->fullTiltDuration(), false, false, isInit, true);
            }
        } else {
            insertShutterMovement(shutterActor, cmd, shutterActor->fullCloseDuration() / m_halfFactor, true, true, isInit, false);
        }
        break;
    case actor::ACTOR_CMD_SHUTTER_HALF_OPEN:
        if (shutterActor->checkTiltSupport()) {
            insertShutterMovement(shutterActor, cmd, shutterActor->fullCloseDuration() / m_halfFactor, true, false, isInit, false);
            insertShutterMovement(shutterActor, cmd, shutterActor->fullCloseDuration() / m_halfFactor, false, false, isInit, true);
        } else {
            iWarning() << "Actor does not support tilting";
        }
        break;
    default:
        break;
    }
}

void ShutterController::insertShutterMovement(ShutterActor* shutterActor, actor::ACTOR_CMDS originalCmd, qint64 duration, bool directionDown, bool updatesStatus, bool isInit, bool isTilt) {
    QMutexLocker locker(&m_activeShutterMovementsMutex);

    ActiveShutterMovement movement;

    movement.shutterActor = shutterActor;
    movement.relayActor = directionDown ? m_actorsDown.value(shutterActor) : m_actorsUp.value(shutterActor);
    movement.originalCmd = originalCmd;
    movement.duration = duration;
    movement.startedAt = -1;
    movement.directionDown = directionDown;
    movement.updatesStatus = updatesStatus;
    movement.isInit = isInit;
    movement.isTilt = isTilt;

    m_activeShutterMovements.enqueue(movement);
}

bool ShutterController::checkShutterInitMovements(ShutterActor* shutterActor, actor::ACTOR_CMDS cmd) {
    QMutexLocker locker(&m_activeShutterMovementsMutex);

    QMutableListIterator<ActiveShutterMovement> it(m_activeShutterMovements);
    while(it.hasNext()) {
        ActiveShutterMovement movement = it.next();
        if (movement.shutterActor->id() == shutterActor->id()) {
            if (movement.isInit) return false;          // init cannot be cancelled
            if (movement.originalCmd != cmd) {
                if (cmd == actor::ACTOR_CMD_UP && movement.originalCmd == actor::ACTOR_CMD_DOWN) {
                    it.remove();
                } else if (cmd == actor::ACTOR_CMD_DOWN && movement.originalCmd == actor::ACTOR_CMD_UP) {
                    it.remove();
                } else {
                    // other cmds must be executed, otherwise out of sync
                }
            } else {
                // same cmd already in pipeline
            }
            break;
        }
    }

    return true;
}
