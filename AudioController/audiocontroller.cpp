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
    for (QAudioDeviceInfo audioDeviceInfo : QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
        iInfo() << audioDeviceInfo.deviceName();
        QAudioOutput* audioOutput = new QAudioOutput(audioDeviceInfo, audioDeviceInfo.preferredFormat());
        connect(audioOutput, &QAudioOutput::stateChanged, this, &AudioController::onStateChanged);
        connect(audioOutput, &QAudioOutput::notify, this, &AudioController::onNotify);
        m_audioOutputs.insert(audioDeviceInfo.deviceName(), audioOutput);
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

        Q_ASSERT(m_audioOutputs.contains(audioActor->audioDeviceId()));
    }
}

void AudioController::onStartPlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());

    //if (m_audioOutputs.contains(audioActor->audioDeviceId()) && m_audioOutputs.value(audioActor->audioDeviceId()).actor->priority() > audioActor->priority()) {
    //    iWarning() << "Higher prio process already running on device" << audioActor->audioDeviceId();
    //} else {
        executeActivation(audioActor, true);
        startPlayback(audioActor);
    //}
}

void AudioController::onPausePlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    executeActivation(audioActor, false);
    pausePlayback(audioActor);
}

void AudioController::onStopPlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    executeActivation(audioActor, false);
    stopPlayback(audioActor);
}

void AudioController::startPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << audioActor->id();

    QAudioOutput *output = m_audioOutputs.value(audioActor->audioDeviceId());
    if (output->state() == QAudio::SuspendedState) {
        output->resume();
    } else {
        output->stop();

        if (audioActor->rawValue().isValid()) {
            QIODevice *device = getMediaDevice(audioActor->rawValue().toString());

            if (device != nullptr) {
                output->start(device);
            }
        } else {
            iWarning() << "Cannot playback - no url set";
        }
    }
}

void AudioController::pausePlayback(AudioPlaybackActor *audioActor) {
    iInfo() << audioActor->id();
    m_audioOutputs.value(audioActor->audioDeviceId())->suspend();
}

void AudioController::stopPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << audioActor->id();

    m_audioOutputs.value(audioActor->audioDeviceId())->stop();
}

void AudioController::executeActivation(AudioPlaybackActor *audioActor, bool activate) {
    iInfo() << audioActor->id();

    if (m_actorRelayMappings.contains(audioActor)) {
        DigitalActor *relayActor = m_actorRelayMappings.value(audioActor);
        m_actorManager->publishCmd(relayActor, activate ? actor::ACTOR_CMD_ON : actor::ACTOR_CMD_OFF);
    }
}

QIODevice* AudioController::getMediaDevice(QString url) {
    iDebug() << Q_FUNC_INFO << url;

    if (QFile::exists(url) && url.endsWith(".wav")) {
        // TODO: support others
        QFile *file = new QFile(url);
        return file;
    } else {
        iWarning() << "Unsupported file" << url;
        return nullptr;
    }
}

void AudioController::onStateChanged(QAudio::State state) {
    QAudioOutput* output = static_cast<QAudioOutput*>(sender());
    iInfo() << Q_FUNC_INFO << output << state;
}

void AudioController::onNotify() {
    QAudioOutput* output = static_cast<QAudioOutput*>(sender());
    iDebug() << output->elapsedUSecs();
}
