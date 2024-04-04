#include "togglecontroller.h"
#include "actor/toggleactor.h"
#include "helpers.h"

#include <QDebug>

ToggleController::ToggleController(ControllerManager *manager, QString id, QObject *parent)
    : ControllerBase(manager, id, parent)
{

}

LogCat::LOGCAT ToggleController::logCat() {
    return LogCat::CONTROLLER;
}

void ToggleController::init() {

}

void ToggleController::start() {

}

void ToggleController::handleMessage(ControllerMessage *msg) {
    Q_UNUSED(msg)
}

void ToggleController::bindManager(ActorManager* actorManager, ValueManagerBase *valueManager) {
    iDebug() << Q_FUNC_INFO;

    this->valueManager = valueManager;

    for (ActorBase *actor : actorManager->actors()) {
        if (qobject_cast<ToggleActor*>(actor) != nullptr) {
            ToggleActor* toggleActor = qobject_cast<ToggleActor*>(actor);
            iInfo() << "Connecting to toggle actor" <<  toggleActor->fullId();
            //Helpers::safeConnect(toggleActor, &ToggleActor::requestToggle, this, &ToggleController::onRequestToggle, SIGNAL(requestToggle()), SLOT(onRequestToggle()));
        }
    }
}


void ToggleController::onRequestToggle() {
    ToggleActor* toggleActor = static_cast<ToggleActor*>(sender());

    iDebug() << Q_FUNC_INFO << toggleActor->fullId();

    valueManager->updateAndPublishValue(toggleActor, !toggleActor->rawValue().toBool());
}
