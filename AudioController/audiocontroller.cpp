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

    m_actorManager = m_manager->getManager<ActorManager>(ActorManager::MANAGER_ID);
    Q_ASSERT(m_actorManager != nullptr);

    iInfo() << "Default output device" << QAudioDeviceInfo::defaultOutputDevice().deviceName();

    iInfo() << "Available audio devices:";
    for (QAudioDeviceInfo audioDeviceInfo : QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
        iInfo() << audioDeviceInfo.deviceName();
        QAudioOutput* audioOutput = new QAudioOutput(audioDeviceInfo, audioDeviceInfo.preferredFormat());
        iInfo() << audioOutput->format();
        connect(audioOutput, &QAudioOutput::stateChanged, this, &AudioController::onStateChanged);
        connect(audioOutput, &QAudioOutput::notify, this, &AudioController::onNotify);
        audioOutput->setObjectName(audioDeviceInfo.deviceName());
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
        iInfo() << "Init audio actor" << audioActor->fullId();

        Helpers::safeConnect(audioActor, &AudioPlaybackActor::startPlaybackRequested, this, &AudioController::onStartPlayback, SIGNAL(startPlaybackRequested()), SLOT(onStartPlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::pausePlaybackRequested, this, &AudioController::onPausePlayback, SIGNAL(pausePlaybackRequested()), SLOT(onPausePlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::stopPlaybackRequested, this, &AudioController::onStopPlayback, SIGNAL(stopPlaybackRequested()), SLOT(onStopPlayback()));

        if (!audioActor->audioActivationRelayId().isEmpty()) {
            DigitalActor* relayActor = static_cast<DigitalActor*>(datamodel->actor(audioActor->audioActivationRelayId()));
            Q_ASSERT(relayActor != nullptr);
            m_actorRelayMappings.insert(audioActor, relayActor);
        }

        m_audioActors.insert(audioActor->audioDeviceId(), audioActor);
        m_audioOutputs.value(audioActor->audioDeviceId())->setVolume(audioActor->audioVolume());
        Q_ASSERT(m_audioOutputs.contains(audioActor->audioDeviceId()));
    }
}

void AudioController::onStartPlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());

    //if (m_audioOutputs.contains(audioActor->audioDeviceId()) && m_audioOutputs.value(audioActor->audioDeviceId()).actor->priority() > audioActor->priority()) {
    //    iWarning() << "Higher prio process already running on device" << audioActor->audioDeviceId();
    //} else {
        startPlayback(audioActor);
    //}
}

void AudioController::onPausePlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    pausePlayback(audioActor);
}

void AudioController::onStopPlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
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
                _start(audioActor, device, output);
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

    _stop(audioActor);
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
    iInfo() << Q_FUNC_INFO << output << state << output->elapsedUSecs();

    switch(state) {
    case QAudio::ActiveState:
    case QAudio::SuspendedState:
        break;
    case QAudio::IdleState:
        if (output->elapsedUSecs() > 0) {
            // playback finished
            _stop(m_audioActors.value(output->objectName()));
        }
    }
}

void AudioController::onNotify() {
    QAudioOutput* output = static_cast<QAudioOutput*>(sender());
    iDebug() << output->elapsedUSecs();
}

void AudioController::_start(AudioPlaybackActor *audioActor, QIODevice *device, QAudioOutput *output) {
    QMutexLocker locker(&m_mutex);

    executeActivation(audioActor, true);

    m_audioDevices.insert(audioActor->audioDeviceId(), device);
    device->open(QIODevice::ReadOnly);
    output->start(device);
}

void AudioController::_stop(AudioPlaybackActor *audioActor) {
    QMutexLocker locker(&m_mutex);

    executeActivation(audioActor, false);

    m_audioOutputs.value(audioActor->audioDeviceId())->stop();
    QIODevice *device = m_audioDevices.value(audioActor->audioDeviceId());
    device->close();
    device->deleteLater();
}
