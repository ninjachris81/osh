#include "audiocontrollersimulator.h"

#include <QDebug>

AudioControllerSimulator::AudioControllerSimulator(ControllerManager *manager, QString id, QObject *parent) : AudioControllerBase(manager, id, parent)
{

}

void AudioControllerSimulator::startPlayback(AudioPlaybackActor *audioActor) {
    iDebug() << Q_FUNC_INFO << audioActor;
}

void AudioControllerSimulator::pausePlayback(AudioPlaybackActor *audioActor) {
    iDebug() << Q_FUNC_INFO << audioActor;
}

void AudioControllerSimulator::stopPlayback(AudioPlaybackActor *audioActor) {
    iDebug() << Q_FUNC_INFO << audioActor;
}
