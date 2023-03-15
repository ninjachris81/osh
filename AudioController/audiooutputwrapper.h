#ifndef AUDIOOUTPUTWRAPPER_H
#define AUDIOOUTPUTWRAPPER_H

#include <QObject>

#include <QAudioOutput>
#include "actor/audioplaybackactor.h"
#include "identifyable.h"

class AudioOutputWrapper : public QAudioOutput, public Identifyable
{
    Q_OBJECT
public:
    explicit AudioOutputWrapper(QString id, const QAudioDeviceInfo &audioDeviceInfo, const QAudioFormat &format = QAudioFormat(), QObject *parent = nullptr);

    void submitPlayback(AudioPlaybackActor *audioActor);
    void cancelPlayback(AudioPlaybackActor *audioActor);
    void nextPlayback(AudioPlaybackActor *audioActor);
    void previousPlayback(AudioPlaybackActor *audioActor);

    void _start(AudioPlaybackActor *audioActor, qint64 startPosition = 0);
    void _stop(AudioPlaybackActor *audioActor);
    void _cleanup();

private:
    QIODevice *m_currentPlaybackDevice = nullptr;
    AudioPlaybackActor *m_currentAudioActor = nullptr;

    QMap<AudioPlaybackActor*, qint64> m_playbackRequests;

    QIODevice* getMediaDevice(QString url);

    void checkStartNext();

private slots:
    void onStateChanged(QAudio::State state);
    void onNotify();


signals:
    void requestActivation(AudioPlaybackActor *audioActor);
    void requestDeactivation(AudioPlaybackActor *audioActor);

};

#endif // AUDIOOUTPUTWRAPPER_H
