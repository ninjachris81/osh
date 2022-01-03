#include "audiocontroller.h"

#include <QFile>

AudioController::AudioController(ControllerManager *manager, QString id, QObject *parent) : AudioControllerBase(manager, id, parent)
{

}

void AudioController::init() {
    iDebug() << Q_FUNC_INFO;

    m_playbackCmd = m_config->getString(this, "playbackCmd", "/usr/bin/aplay");
    m_playbackFile = m_config->getString(this, "playbackFile", "/opt/osh/AudioService/audio/test.wav");

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
}
