#include "audiocontroller.h"

#include <QFile>
#include <QAudioDeviceInfo>

#include "macros.h"
#include "actor/actormessage.h"
#include "helpers.h"
#include "controller/controllermanager.h"

AudioController::AudioController(ControllerManager *manager, QString id, QObject *parent) : AudioControllerBase(manager, id, parent)
{
}

void AudioController::init() {
    iDebug() << Q_FUNC_INFO;

    m_playbackCmd = m_config->getString(this, "playbackCmd", "/usr/bin/aplay");

    if (!QFile::exists(m_playbackCmd)) iWarning() << "Cmd file" << m_playbackCmd << "does not exist!";

    m_actorManager = m_manager->getManager<ActorManager>(ActorManager::MANAGER_ID);
    Q_ASSERT(m_actorManager != nullptr);

    iInfo() << "Available audio devices:";

    for (QAudioDeviceInfo audioDevice : QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
        iInfo() << audioDevice.deviceName();
    }
}

void AudioController::start() {
    iDebug() << Q_FUNC_INFO;
}

void AudioController::loadAudioActors(DatamodelBase *datamodel) {
    iInfo() << Q_FUNC_INFO;

    for (ActorBase* actor : datamodel->actors(this->id())) {
        AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(actor);

        Helpers::safeConnect(audioActor, &AudioPlaybackActor::startPlaybackRequested, this, &AudioController::onStartPlayback, SIGNAL(startPlaybackRequested()), SLOT(onStartPlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::pausePlaybackRequested, this, &AudioController::onPausePlayback, SIGNAL(pausePlaybackRequested()), SLOT(onPausePlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::stopPlaybackRequested, this, &AudioController::onStopPlayback, SIGNAL(stopPlaybackRequested()), SLOT(onStopPlayback()));

        if (!audioActor->audioActivationRelayId().isEmpty()) {
            DigitalActor* relayActor = static_cast<DigitalActor*>(datamodel->actor(audioActor->audioActivationRelayId()));
            Q_ASSERT(relayActor != nullptr);
            m_actorRelayMappings.insert(audioActor, relayActor);
        }
    }
}

void AudioController::onStartPlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());

    if (m_playbackProcesses.contains(audioActor->audioDeviceId()) && m_playbackProcesses.value(audioActor->audioDeviceId()).actor->priority() > audioActor->priority()) {
        iWarning() << "Higher prio process already running on device" << audioActor->audioDeviceId();
    } else {
        executeActivation(audioActor, true);
        startPlayback(audioActor);
    }
}

void AudioController::onPausePlayback() {
    // currently not supported
}

void AudioController::onStopPlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    executeActivation(audioActor, false);
    stopPlayback(audioActor);
}

void AudioController::startPlayback(AudioPlaybackActor *audioActor) {
    QMutexLocker mutexLocker(&m_playbackProcessMutex);
    iInfo() << audioActor->id();

    stopPlayback(audioActor);

    if (audioActor->rawValue().isValid()) {
        QString playbackUrl = audioActor->rawValue().toString();

        if (validatePlaybackUrl(playbackUrl)) {
#ifdef Q_OS_WIN
            iWarning() << "Ignoring playback request (windows)" << playbackUrl;
#else
            QProcess* proc = new QProcess();
            proc->start(m_playbackCmd, QStringList() << playbackUrl);
            AudioProcess audioProcInfo;
            audioProcInfo.process = proc;
            audioProcInfo.actor = audioActor;
            m_playbackProcesses.insert(audioActor->audioDeviceId(), audioProcInfo);
#endif
        } else {
            iWarning() << "Playback file" << playbackUrl << "does not exist!";
        }
    } else {
        iWarning() << "Cannot playback - no url set";
    }
}

void AudioController::pausePlayback(AudioPlaybackActor *audioActor) {
    QMutexLocker mutexLocker(&m_playbackProcessMutex);

    iInfo() << audioActor->id();

    QProcess* proc = m_playbackProcesses.value(audioActor->audioDeviceId()).process;
    proc->terminate();
    proc->deleteLater();
    m_playbackProcesses.remove(audioActor->audioDeviceId());
}

void AudioController::stopPlayback(AudioPlaybackActor *audioActor) {
    QMutexLocker mutexLocker(&m_playbackProcessMutex);
    iInfo() << audioActor->id();

    QProcess* proc = m_playbackProcesses.value(audioActor->audioDeviceId()).process;
    proc->terminate();
    proc->deleteLater();
    m_playbackProcesses.remove(audioActor->audioDeviceId());
}

void AudioController::executeActivation(AudioPlaybackActor *audioActor, bool activate) {
    iInfo() << audioActor->id();

    if (m_actorRelayMappings.contains(audioActor)) {
        DigitalActor *relayActor = m_actorRelayMappings.value(audioActor);
        m_actorManager->publishCmd(relayActor, activate ? actor::ACTOR_CMD_ON : actor::ACTOR_CMD_OFF);
    }
}

bool AudioController::validatePlaybackUrl(QString url) {
    iDebug() << Q_FUNC_INFO << url;

    // TODO: support others

    return QFile::exists(url);
}
