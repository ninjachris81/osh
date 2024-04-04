#include "dooraudio_controller.h"

#include <QDebug>
#include <QTimer>
#include <QThread>

#include "controller/controllermanager.h"
#include "shared/controllercmdtypes_qt.h"
#include "controller/controllermessage.h"

#include "helpers.h"

DoorAudioController::DoorAudioController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{
}

void DoorAudioController::init() {
    iDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    m_endpoint.init();

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ActorManager);
    m_actorManager = m_manager->getManager<ActorManager>(ActorManager::MANAGER_ID);

    QString registrarIp = m_config->getString(this, "sipRegistrarIp", "localhost");
    QString sipId = m_config->getString(this, "sipId", "5001");
    QString sipPassword = m_config->getString(this, "sipPassword", "test123");
    m_sipRingId = m_config->getString(this, "sipRingId", "6000");

    m_account = new OshAccount(this, registrarIp, sipId, sipPassword);
}

void DoorAudioController::start() {
    iDebug() << Q_FUNC_INFO;

    Helpers::safeConnect(m_doorRingActor, &DigitalActor::cmdTriggered, this, &DoorAudioController::onRingTriggered, SIGNAL(cmdTriggered(actor::ACTOR_CMDS)), SLOT(onRingTriggered(actor::ACTOR_CMDS)));
    Helpers::safeConnect(m_account, &OshAccount::stateChanged, this, &DoorAudioController::onCallStateChanged, SIGNAL(stateChanged(OshCall::OshCallState)), SLOT(onCallStateChanged(OshCall::OshCallState)));
}

void DoorAudioController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void DoorAudioController::onCallStateChanged(int newState) {
    iInfo() << Q_FUNC_INFO << newState << QThread::currentThreadId();
    OshCall::OshCallState state = static_cast<OshCall::OshCallState>(newState);

    switch(state) {
    case OshCall::RINGING:
        //m_actorManager->publishCmd(m_doorRingActor, actor::ACTOR_CMD_ON, true);
        m_valueManager->updateAndPublishValue(m_doorRingActor, true);
        break;
    case OshCall::IDLE:
    case OshCall::ACTIVE:
        m_valueManager->updateAndPublishValue(m_doorRingActor, false);
        break;
    }
}

void DoorAudioController::bindDoorRingActor(DigitalActor *doorRingActor) {
    this->m_doorRingActor = doorRingActor;
}

void DoorAudioController::onRingTriggered(actor::ACTOR_CMDS cmd) {
    switch(cmd) {
    case actor::ACTOR_CMD_ON:
        m_account->startCall(m_sipRingId);
        break;
    case actor::ACTOR_CMD_OFF:
        m_account->cancelCall();
        break;
    default:
        break;
    }
}
