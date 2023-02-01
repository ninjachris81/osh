#include "audiocontrollersimulator.h"

#include <QDebug>

AudioControllerSimulator::AudioControllerSimulator(ControllerManager *manager, QString id, QObject *parent) : AudioControllerBase(manager, id, parent)
{

}

quint8 AudioControllerSimulator::channelCount() {
    return 4;
}

void AudioControllerSimulator::startPlayback(quint8 index) {
    iDebug() << Q_FUNC_INFO << index;
}

void AudioControllerSimulator::pausePlayback(quint8 index) {
    iDebug() << Q_FUNC_INFO << index;
}

void AudioControllerSimulator::stopPlayback(quint8 index) {
    iDebug() << Q_FUNC_INFO << index;
}
