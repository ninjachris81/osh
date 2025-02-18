#include "audiooutputwrapper.h"
#include "audiofiledevice.h"
#include "audioplaylistdevice.h"
#include "audiostreamdevice.h"

#include <QFile>

AudioOutputWrapper::AudioOutputWrapper(QString id, const QAudioDeviceInfo &audioDeviceInfo, const QAudioFormat &format, QObject *parent)
    : QAudioOutput(audioDeviceInfo, format, parent), Identifyable(id)
{
    iInfo() << this->format();
    connect(this, &QAudioOutput::stateChanged, this, &AudioOutputWrapper::onStateChanged);
    connect(this, &QAudioOutput::notify, this, &AudioOutputWrapper::onNotify);
    this->setObjectName(id);
}

void AudioOutputWrapper::onStateChanged(QAudio::State state) {
    QAudioOutput* output = static_cast<QAudioOutput*>(sender());
    iInfo() << Q_FUNC_INFO << output << state << output->elapsedUSecs();

    switch(state) {
        case QAudio::ActiveState:
        case QAudio::SuspendedState:
            break;
        case QAudio::IdleState:
            if (output->elapsedUSecs() > 0) {
                // playback finished
                _stop(m_currentAudioActor);
            }
        default:
            break;
    }
}

void AudioOutputWrapper::checkStartNext() {
    iDebug() << Q_FUNC_INFO;

    AudioPlaybackActor* nextAudioActor = nullptr;
    for (AudioPlaybackActor* audioActor : m_playbackRequests.keys()) {
        if (nextAudioActor == nullptr) {
            nextAudioActor = audioActor;
        } else if (nextAudioActor->priority() < audioActor->priority()) {
            nextAudioActor = audioActor;
        }
    }

    if (nextAudioActor != nullptr) {
        qint64 startPosition = m_playbackRequests.value(nextAudioActor);
        m_playbackRequests.remove(nextAudioActor);
        _start(nextAudioActor, startPosition);
    }
}

void AudioOutputWrapper::_start(AudioPlaybackActor* audioActor, qint64 startPosition) {
    iInfo() << Q_FUNC_INFO;

    if (m_currentPlaybackDevice != nullptr) {
        _cleanup();
    }

    m_currentAudioActor= audioActor;
    Q_EMIT(requestDeactivation(m_currentAudioActor));

    qint64 startPositionHint = startPosition;
    m_currentPlaybackDevice = getMediaDevice(audioActor->audioUrl(), startPositionHint);
    m_currentPlaybackDevice->open(QIODevice::ReadOnly);
    if (startPositionHint > 0) {
        m_currentPlaybackDevice->seek(startPositionHint);
    }
    this->setVolume(audioActor->audioVolume());
    this->start(m_currentPlaybackDevice);
}

void AudioOutputWrapper::_stop(AudioPlaybackActor *audioActor) {
    if (m_currentAudioActor == audioActor && m_currentPlaybackDevice != nullptr) {
        if (m_playbackRequests.isEmpty() && !m_currentAudioActor->audioDeviceIds().isEmpty()) {
            Q_EMIT(requestDeactivation(m_currentAudioActor));
        }

        // stop current playback
        _cleanup();

        checkStartNext();
    } else {
        // check delete in queue
        if (m_playbackRequests.contains(audioActor)) {
            m_playbackRequests.remove(audioActor);
        }
    }
}

void AudioOutputWrapper::_cleanup() {
    stop();
    m_currentPlaybackDevice->close();
    m_currentPlaybackDevice->deleteLater();
    m_currentPlaybackDevice = nullptr;
    m_currentAudioActor = nullptr;
}

void AudioOutputWrapper::onNotify() {
    QAudioOutput* output = static_cast<QAudioOutput*>(sender());
    iDebug() << output->elapsedUSecs();
}

void AudioOutputWrapper::submitPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << Q_FUNC_INFO << audioActor->fullId();

    if (m_currentAudioActor == nullptr) {
        // new request
        iDebug() << "Direct new playback" << audioActor->fullId();
        _start(audioActor);
    } else if (m_currentAudioActor != nullptr && m_currentAudioActor == audioActor) {
        // current playback of audio actor, replace it
        iDebug() << "Direct start of playback" << audioActor->fullId();
        _start(audioActor);
    } else if (m_playbackRequests.contains(audioActor)) {
        // already scheduled playback, so stop it and replace it with new one
        iDebug() << "Replacing already scheduled playback" << audioActor->fullId();
        m_playbackRequests.insert(audioActor, 0);
    } else if (m_currentAudioActor != nullptr && m_currentAudioActor!=audioActor && audioActor->priority() > m_currentAudioActor->priority()) {
        // higher prio task, back up current one and start higher one
        iDebug() << "Replacing current playback with higher playback" << audioActor->fullId();
        m_playbackRequests.insert(m_currentAudioActor, m_currentPlaybackDevice->pos());
        _start(audioActor);
    } else {
        iDebug() << "Scheduling new playback" << audioActor->fullId();
        m_playbackRequests.insert(audioActor, 0);
    }
}

void AudioOutputWrapper::cancelPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << Q_FUNC_INFO << audioActor->fullId();

    if (m_currentAudioActor == audioActor) {
        iDebug() << "Cancelling current playback" << audioActor->fullId();
        _stop(audioActor);
    } else if (m_playbackRequests.contains(audioActor)) {
        iDebug() << "Cancelling scheduled playback" << audioActor->fullId();
        m_playbackRequests.remove(audioActor);
    }
}

void AudioOutputWrapper::nextPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << Q_FUNC_INFO << audioActor->fullId();

    if (m_currentPlaybackDevice != nullptr) {
        if (m_currentPlaybackDevice->inherits(AudioPlaylistDevice::staticMetaObject.className())) {
            static_cast<AudioPlaylistDevice*>(m_currentPlaybackDevice)->next();
        } else {
            iWarning() << "Current playback does not support method";
        }
    } else {
      iWarning() << "No playback active";
    }
}

void AudioOutputWrapper::previousPlayback(AudioPlaybackActor *audioActor) {
    iInfo() << Q_FUNC_INFO << audioActor->fullId();

    if (m_currentPlaybackDevice != nullptr) {
        if (m_currentPlaybackDevice->inherits(AudioPlaylistDevice::staticMetaObject.className())) {
            static_cast<AudioPlaylistDevice*>(m_currentPlaybackDevice)->previous();
        } else {
            iWarning() << "Current playback does not support method";
        }
    } else {
      iWarning() << "No playback active";
    }
}

QIODevice* AudioOutputWrapper::getMediaDevice(QString url, qint64 &startPositionHint) {
    iDebug() << Q_FUNC_INFO << url;

    if (QFile::exists(url) && url.endsWith(".wav")) {
        // TODO: support others
        QFile *file = new QFile(url);
        startPositionHint = 0x4e;
        return file;
    } else if (QFile::exists(url) && url.endsWith(".m3u")) {
        AudioPlaylistDevice *playlist = new AudioPlaylistDevice(url);
        return playlist;
    } else if (url.startsWith("http") || url.startsWith("https")) {
        AudioStreamDevice *audioStream = new AudioStreamDevice(url);
        return audioStream;
    } else if (QFile::exists(url) && url.endsWith(".mp3")) {
        AudioFileDevice *stream = new AudioFileDevice(url, this->format());
        return stream;
    } else {
        iWarning() << "Unsupported file" << url;
        return nullptr;
    }
}
