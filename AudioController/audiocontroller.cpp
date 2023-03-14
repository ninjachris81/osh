#include "audiocontroller.h"

#include <QFile>
#include <QAudioDeviceInfo>

#include "audiofilestream.h"
#include "audiooutputwrapper.h"
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

    initAvailableDevices();
}

void AudioController::start() {
    iDebug() << Q_FUNC_INFO;
}

void AudioController::loadAudioActors(DatamodelBase *datamodel, ClientValueManager* valueManager) {
    iInfo() << Q_FUNC_INFO;

    for (ActorBase* actor : datamodel->actors(this->id())) {
        AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(actor);
        iInfo() << "Init audio actor" << audioActor->fullId();

        Helpers::safeConnect(audioActor, &AudioPlaybackActor::startPlaybackRequested, this, &AudioController::onStartPlayback, SIGNAL(startPlaybackRequested()), SLOT(onStartPlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::pausePlaybackRequested, this, &AudioController::onPausePlayback, SIGNAL(pausePlaybackRequested()), SLOT(onPausePlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::stopPlaybackRequested, this, &AudioController::onStopPlayback, SIGNAL(stopPlaybackRequested()), SLOT(onStopPlayback()));
        Helpers::safeConnect(audioActor, &AudioPlaybackActor::volumeChanged, this, &AudioController::onVolumeChanged, SIGNAL(volumeChanged()), SLOT(onVolumeChanged()));

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

        for (QString audioDeviceId : audioActor->audioDeviceIds()) {
            initDevice(audioDeviceId, audioActor);
        }
    }
}

void AudioController::initAvailableDevices() {
    iInfo() << "Available audio devices:";
    for (QAudioDeviceInfo audioDeviceInfo : QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
        iInfo() << audioDeviceInfo.deviceName();
        m_availableDeviceInfos.insert(audioDeviceInfo.deviceName(), audioDeviceInfo);
    }
}

void AudioController::initDevice(QString deviceName, AudioPlaybackActor* playbackActor) {
    iInfo() << Q_FUNC_INFO << deviceName;

    Q_ASSERT(m_availableDeviceInfos.contains(deviceName));
    QAudioDeviceInfo audioDeviceInfo = m_availableDeviceInfos.value(deviceName);

    AudioOutputWrapper* audioOutput;
    if (m_audioOutputs.contains(audioDeviceInfo.deviceName())) {
        audioOutput = m_audioOutputs.value(audioDeviceInfo.deviceName());
    } else {
        // create a new one
        audioOutput = new AudioOutputWrapper(audioDeviceInfo.deviceName(), audioDeviceInfo, audioDeviceInfo.preferredFormat());
    }

    m_audioOutputMappings.insert(playbackActor, audioOutput);

    m_audioOutputs.insert(audioDeviceInfo.deviceName(), audioOutput);

    if (!playbackActor->audioActivationRelayId().isEmpty()) {
        connect(audioOutput, &AudioOutputWrapper::requestActivation, [this](AudioPlaybackActor* audioActor){
            executeActivation(audioActor, true);
        });

        connect(audioOutput, &AudioOutputWrapper::requestDeactivation, [this](AudioPlaybackActor* audioActor){
            executeActivation(audioActor, false);
        });
    }
}

void AudioController::onStartPlayback() {
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());

    startPlayback(audioActor);
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

    if (audioActor->rawValue().isValid()) {
        QListIterator<AudioOutputWrapper*> it(m_audioOutputMappings.values(audioActor));
        while (it.hasNext()) {
            AudioOutputWrapper *output = it.next();
            output->submitPlayback(audioActor);
        }
    } else {
        iWarning() << "Cannot playback - no url set";
    }
}

void AudioController::pausePlayback(AudioPlaybackActor *audioActor) {
    iInfo() << audioActor->id();
    //m_audioOutputs.value(audioActor->audioDeviceId())->suspend();
}

void AudioController::stopPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << audioActor->id();

    QListIterator<AudioOutputWrapper*> it(m_audioOutputMappings.values(audioActor));
    while (it.hasNext()) {
        AudioOutputWrapper *output = it.next();
        output->cancelPlayback(audioActor);
    }
}

void AudioController::onVolumeChanged() {
    iInfo() << Q_FUNC_INFO;
    AudioPlaybackActor* audioActor = static_cast<AudioPlaybackActor*>(sender());
    QListIterator<AudioOutputWrapper*> it(m_audioOutputMappings.values(audioActor));
    while (it.hasNext()) {
        AudioOutputWrapper *output = it.next();
        output->setVolume(audioActor->audioVolume());
    }

}

void AudioController::executeActivation(AudioPlaybackActor *audioActor, bool activate) {
    iInfo() << audioActor->id();

    if (m_actorRelayMappings.contains(audioActor)) {
        DigitalActor *relayActor = m_actorRelayMappings.value(audioActor);
        m_actorManager->publishCmd(relayActor, activate ? actor::ACTOR_CMD_ON : actor::ACTOR_CMD_OFF);
    }
}

