#include "doorcamera_controller.h"

#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QFile>
#include <QDir>

#include "controller/controllermanager.h"
#include "shared/controllercmdtypes_qt.h"
#include "controller/controllermessage.h"

#include "helpers.h"

DoorCameraController::DoorCameraController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{
}

void DoorCameraController::init() {
    iDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ActorManager);
    m_actorManager = m_manager->getManager<ActorManager>(ActorManager::MANAGER_ID);

    m_program = m_config->getString(this, "program", "/usr/bin/openRTSP");
    m_duration = m_config->getInt(this, "duration", 30000);
    rtspUrl = m_config->getString(this, "rtspUrl", "rtsp://localhost:554");
    baseStorageUrl = m_config->getString(this, "baseStorageUrl", "/var/ftp_data/videos");
}

void DoorCameraController::start() {
    iDebug() << Q_FUNC_INFO;

    Helpers::safeConnect(m_doorRingActor, &DigitalActor::cmdTriggered, this, &DoorCameraController::onRingTriggered, SIGNAL(cmdTriggered(actor::ACTOR_CMDS)), SLOT(onRingTriggered(actor::ACTOR_CMDS)));
}

void DoorCameraController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void DoorCameraController::bindDoorRingActor(DigitalActor *doorRingActor) {
    this->m_doorRingActor = doorRingActor;
}

void DoorCameraController::onRingTriggered(actor::ACTOR_CMDS cmd) {
    iInfo() << Q_FUNC_INFO << cmd;

    switch(cmd) {
    case actor::ACTOR_CMD_ON:
        startRecording();
        break;
    case actor::ACTOR_CMD_OFF:
        break;
    default:
        break;
    }
}


void DoorCameraController::startRecording() {
    iInfo() << Q_FUNC_INFO;

    QProcess *proc = new QProcess();
    proc->setProgram(m_program);
    proc->setArguments(QStringList() << "-4" << "-d" << QString::number(m_duration) << rtspUrl);
    QString videoDir = baseStorageUrl + QDir::separator() + QDateTime::currentDateTime().toString("yyyyMMdd");
    QDir videoPath(videoDir);
    iInfo() << "mkpath" << videoPath.mkpath(videoDir);
    proc->setStandardOutputFile(videoDir + QDir::separator() + QDateTime::currentDateTime().toString("yyMMddhhmmsszzz") + ".mp4");
    connect(proc, SIGNAL(finished(int)), proc, SLOT(deleteLater()));
    iInfo() << "Starting" << proc;
    proc->start();
}
