#include "audiocontroller.h"

#include <QFile>
#include "macros.h"
#include "actor/actormessage.h"

AudioController::AudioController(ControllerManager *manager, QString id, QObject *parent) : AudioControllerSimulator(manager, id, parent)
{
}

void AudioController::init() {
    iDebug() << Q_FUNC_INFO;

    m_playbackCmd = m_config->getString(this, "playbackCmd", "/usr/bin/aplay");
    m_playbackFile = m_config->getString(this, "playbackFile", "/opt/osh/AudioService/audio/test.wav");

    m_activateAmplGroupId = m_config->getString(this, "activateAmplGroupId", "");
    m_activateAmplActorId = m_config->getString(this, "activateAmplActorId", "");

    if (!QFile::exists(m_playbackCmd)) iWarning() << "Cmd file" << m_playbackCmd << "does not exist!";
    if (!QFile::exists(m_playbackFile)) iWarning() << "Playback file" << m_playbackFile << "does not exist!";
}

void AudioController::start() {
    iDebug() << Q_FUNC_INFO;
}

quint8 AudioController::channelCount() {
    return 1;
}

void AudioController::startPlayback(quint8 channelIndex) {
    stopPlayback(channelIndex);

    if (!m_activateAmplGroupId.isEmpty() && !m_activateAmplActorId.isEmpty()) {
        Q_EMIT(requestActivation(m_activateAmplGroupId, m_activateAmplActorId, true));
    }

#ifdef Q_OS_WIN
    iWarning() << "Ignoring playback request (windows)";
#else
    m_playbackProcess.start(m_playbackCmd, QStringList() << m_playbackFile);
#endif
}

void AudioController::pausePlayback(quint8 channelIndex) {
    m_playbackProcess.terminate();
}

void AudioController::stopPlayback(quint8 channelIndex) {
    m_playbackProcess.terminate();
    if (!m_activateAmplGroupId.isEmpty() & !m_activateAmplActorId.isEmpty()) {
        Q_EMIT(requestActivation(m_activateAmplGroupId, m_activateAmplActorId, false));
    }
}

void AudioController::bindCommunicationManager(CommunicationManagerBase *commManager) {
    m_commManager = commManager;

    connect(this, &AudioController::requestActivation, [this](QString amplGroupdId, QString amplActorId, bool activate) {
        ActorMessage msg(amplGroupdId, amplActorId, activate ? ACTOR_CMDS::ACTOR_CMD_ON : ACTOR_CMDS::ACTOR_CMD_OFF);
        m_commManager->sendMessage(msg);
    });
}
