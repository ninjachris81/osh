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

    if (audioActor->rawValue().isValid()) {
        QString audioDeviceId = audioActor->audioDeviceIds().at(0);
        QString url = audioActor->rawValue().toString();

        if (m_runningProcesses.contains(audioDeviceId)) {
            iInfo() << "Terminating running process on" << audioDeviceId;
            QProcess* proc = m_runningProcesses.value(audioDeviceId);
            proc->terminate();
            proc->deleteLater();
        }

        AudioProcessWrapperBase *proc;
        if (url.endsWith(".wav")) {
            iInfo() << "Launch new aplay";
            proc = new APlayProcessWrapper(m_config->getString("aplay", "/usr/bin/aplay"), audioActor);
        } else {
            iInfo() << "Launch new mpg123";
            proc = new MPG123ProcessWrapper(m_config->getString("mpg123", "/usr/bin/mpg123"), audioActor);
        }

        // set initially
        m_volumeWrapper.setVolume(audioActor);

        m_runningProcesses.insert(audioDeviceId, proc);

        proc->start();
    } else {
        iWarning() << "Cannot playback - no url set";
    }
}

void AudioController2::pausePlayback(AudioPlaybackActor *audioActor) {
    iInfo() << audioActor->id();
    //m_audioOutputs.value(audioActor->audioDeviceId())->suspend();
}

void AudioController2::stopPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << audioActor->id();

    if (m_runningProcesses.contains(audioActor->audioDeviceIds().at(0))) {
        iInfo() << "Terminating running process on" << audioActor->audioDeviceIds().at(0);
        QProcess* proc = m_runningProcesses.value(audioActor->audioDeviceIds().at(0));
        proc->terminate();
        proc->deleteLater();
    }

}

void AudioController2::onVolumeChanged() {
    iInfo() << Q_FUNC_INFO;
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    m_volumeWrapper.setVolume(audioActor);
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
