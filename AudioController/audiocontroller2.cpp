#include "audiocontroller2.h"

#include <QFile>
#include <QAudioDeviceInfo>

#include "aplayprocesswrapper.h"
#include "audiofiledevice.h"
#include "audiooutputwrapper.h"
#include "macros.h"
#include "actor/actormessage.h"
#include "helpers.h"
#include "controller/controllermanager.h"
#include "mpg123processwrapper.h"
#include "aplayprocesswrapper.h"

AudioController2::AudioController2(ControllerManager *manager, QString id, QObject *parent) : AudioControllerBase(manager, id, parent)
{
}

void AudioController2::init() {
    iDebug() << Q_FUNC_INFO;

    m_actorManager = m_manager->getManager<ActorManager>(ActorManager::MANAGER_ID);
    Q_ASSERT(m_actorManager != nullptr);

}

void AudioController2::start() {
    iDebug() << Q_FUNC_INFO;
}

void AudioController2::loadAudioActors(DatamodelBase *datamodel, ClientValueManager* valueManager) {
    iInfo() << Q_FUNC_INFO;

    for (ActorBase* actor : datamodel->actors(this->id())) {
        AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(actor);
        iInfo() << "Init audio actor" << audioActor->fullId();

        Helpers::safeConnect(audioActor, &AudioPlaybackActor::startPlaybackRequested, this, &AudioController2::onStartPlayback, SIGNAL(startPlaybackRequested()), SLOT(onStartPlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::pausePlaybackRequested, this, &AudioController2::onPausePlayback, SIGNAL(pausePlaybackRequested()), SLOT(onPausePlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::stopPlaybackRequested, this, &AudioController2::onStopPlayback, SIGNAL(stopPlaybackRequested()), SLOT(onStopPlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::volumeChanged, this, &AudioController2::onVolumeChanged, SIGNAL(volumeChanged()), SLOT(onVolumeChanged()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::urlChanged, this, &AudioController2::onUrlChanged, SIGNAL(urlChanged()), SLOT(onUrlChanged()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::nextRequested, this, &AudioController2::onNext, SIGNAL(nextRequested()), SLOT(onNext()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::previousRequested, this, &AudioController2::onPrevious, SIGNAL(previousRequested()), SLOT(onPrevious()));

        if (!audioActor->audioActivationRelayId().isEmpty()) {
            iInfo() << "Binding relay" << audioActor->audioActivationRelayId();
            DigitalActor* relayActor = static_cast<DigitalActor*>(datamodel->actor(audioActor->audioActivationRelayId()));
            Q_ASSERT(relayActor != nullptr);
            m_actorRelayMappings.insert(audioActor, relayActor);
        }

        if (!audioActor->audioVolumeId().isEmpty()) {
            iInfo() << "Binding volume" << audioActor->audioVolumeId();
            DoubleValue* volumeValue = static_cast<DoubleValue*>(datamodel->value(audioActor->audioVolumeId()));
            Q_ASSERT(volumeValue != nullptr);
            audioActor->withAudioVolumeValue(volumeValue);
            valueManager->registerForNotification(volumeValue);
        }

        if (!audioActor->audioUrlId().isEmpty()) {
            iInfo() << "Binding url" << audioActor->audioUrlId();
            StringValue* urlValue = static_cast<StringValue*>(datamodel->value(audioActor->audioUrlId()));
            Q_ASSERT(urlValue != nullptr);
            audioActor->withAudioUrlValue(urlValue);
            valueManager->registerForNotification(urlValue);
        } else if (audioActor->audioUrl().isEmpty()) {
            iWarning() << "Audio actors must have either url value, or static url set" << audioActor->fullId();
            Q_ASSERT(false);
        }

        m_playbackActors.insert(audioActor->id(), audioActor);
    }
}

void AudioController2::onStartPlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());

    startPlayback(audioActor);
}

void AudioController2::onPausePlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    pausePlayback(audioActor);
}

void AudioController2::onStopPlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    stopPlayback(audioActor);
}

void AudioController2::startPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << audioActor->id();

    if (audioActor->priority() >= 10) {
        // stop all processes
        iInfo() << "High prio playback - stopping all playbacks";
        stopAllProcesses();
    }

    if (!audioActor->audioUrl().isEmpty()) {
        QString audioDeviceId = audioActor->audioDeviceIds().at(0);
        QString url = audioActor->audioUrl();

        if (m_runningProcesses.contains(audioDeviceId)) {
            iInfo() << "Terminating running process on" << audioDeviceId;
            stopProcess(audioDeviceId);
        }

        AudioProcessWrapperBase *proc;
        if (url.endsWith(".wav")) {
            iInfo() << "Launch new aplay";
            proc = new APlayProcessWrapper(m_config->getString("aplay", "/usr/bin/aplay"), audioActor);
        } else {
            iInfo() << "Launch new mpg123";
            proc = new MPG123ProcessWrapper(m_config->getString("mpg123", "/usr/bin/mpg123"), audioActor);
        }

        connect(proc, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &AudioController2::onProcessFinished);
        connect(proc, &QProcess::errorOccurred, this, &AudioController2::onProcessError);

        // set initially
        iInfo() << "Initially setting volume";
        m_volumeWrapper.setVolume(audioActor);

        m_runningProcesses.insert(audioDeviceId, proc);

        iInfo() << "Launching" << proc->program() << proc->arguments();
        audioActor->setPlaybackState(AudioPlaybackActor::PLAYING);
        proc->start();
    } else {
        iWarning() << "Cannot playback - no url set";
    }
}

void AudioController2::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    iInfo() << Q_FUNC_INFO << exitCode << exitStatus;

    AudioProcessWrapperBase *proc = static_cast<AudioProcessWrapperBase*>(sender());
    iInfo() << "Process finished with exit code" << exitCode << exitStatus;
    proc->audioActor()->setPlaybackState(AudioPlaybackActor::STOPPED);
    m_runningProcesses.remove(proc->audioActor()->audioDeviceIds().at(0));
    proc->deleteLater();
}

void AudioController2::onProcessError(QProcess::ProcessError error) {
    iWarning() << Q_FUNC_INFO << error;
    AudioProcessWrapperBase *proc = static_cast<AudioProcessWrapperBase*>(sender());
    proc->audioActor()->setPlaybackState(AudioPlaybackActor::ERROR);
    m_runningProcesses.remove(proc->audioActor()->audioDeviceIds().at(0));
    proc->deleteLater();
}

void AudioController2::pausePlayback(AudioPlaybackActor *audioActor) {
    iInfo() << audioActor->id();
    //m_audioOutputs.value(audioActor->audioDeviceId())->suspend();
}

void AudioController2::stopPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << Q_FUNC_INFO << audioActor->id();

    if (m_runningProcesses.contains(audioActor->audioDeviceIds().at(0))) {
        iInfo() << "Terminating running process on" << audioActor->audioDeviceIds().at(0);
        stopProcess(audioActor->audioDeviceIds().at(0));
    }
}

void AudioController2::stopProcess(QString audioDeviceId) {
    iInfo() << Q_FUNC_INFO << audioDeviceId;

    AudioProcessWrapperBase* proc = m_runningProcesses.value(audioDeviceId);

    iInfo() << "Terminating process" << proc->processId();

    disconnect(proc, 0, this, 0);

    proc->terminate();
    proc->waitForFinished();
    delete proc;
    m_runningProcesses.remove(audioDeviceId);
}

void AudioController2::stopAllProcesses() {
    iInfo() << Q_FUNC_INFO;

    for (QString audioDeviceId : m_runningProcesses.keys()) {
        stopProcess(audioDeviceId);
    }
}


void AudioController2::onVolumeChanged() {
    iInfo() << Q_FUNC_INFO;
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    m_volumeWrapper.setVolume(audioActor);
}

void AudioController2::onUrlChanged() {
    iInfo() << Q_FUNC_INFO;
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    // TODO: restart proc
}

void AudioController2::executeActivation(AudioPlaybackActor *audioActor, bool activate) {
    iInfo() << audioActor->id();

    if (m_actorRelayMappings.contains(audioActor)) {
        DigitalActor *relayActor = m_actorRelayMappings.value(audioActor);
        m_actorManager->publishCmd(relayActor, activate ? actor::ACTOR_CMD_ON : actor::ACTOR_CMD_OFF);
    }
}

void AudioController2::onNext() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    // TODO
}

void AudioController2::onPrevious() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    // TODO
}
