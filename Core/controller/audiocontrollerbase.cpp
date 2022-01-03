#include "audiocontrollerbase.h"

AudioControllerBase::AudioControllerBase(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{

}

void AudioControllerBase::handleMessage(ControllerMessage *msg) {

}

quint8 AudioControllerBase::bindActor(AudioPlaybackActor* actor) {
    quint8 audioInstanceIndex = m_actorMappings.count();
    m_actorMappings.append(actor);
    QObject::connect(actor, &AudioPlaybackActor::startPlaybackRequested, [this, audioInstanceIndex]() {
        startPlayback(audioInstanceIndex);
    });
    QObject::connect(actor, &AudioPlaybackActor::pausePlaybackRequested, [this, audioInstanceIndex]() {
        pausePlayback(audioInstanceIndex);
    });
    QObject::connect(actor, &AudioPlaybackActor::stopPlaybackRequested, [this, audioInstanceIndex]() {
        stopPlayback(audioInstanceIndex);
    });
    return audioInstanceIndex;
}

