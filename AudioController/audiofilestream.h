#ifndef AUDIOFILESTREAM_H
#define AUDIOFILESTREAM_H

#include <QIODevice>
#include <QBuffer>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QFile>

#include "sharedlib.h"

// Class for decode audio files like MP3 and push decoded audio data to QOutputDevice (like speaker) and also signal newData().
// For decoding it uses QAudioDecoder which uses QAudioFormat for decode audio file for desire format, then put decoded data to buffer.
// based on: https://github.com/Znurre/QtMixer
class SHARED_LIB_EXPORT AudioFileStream : public QIODevice
{
    Q_OBJECT

public:
    AudioFileStream();
    bool init(const QAudioFormat& format, QString filePath);

    enum State { Playing, Stopped };

    void play();
    /*virtual*/ bool open(OpenMode mode) override;


    void stop();

    bool atEnd() const override;

protected:
    qint64 readData(char* data, qint64 maxlen) override;
    qint64 writeData(const char* data, qint64 len) override;

private:
    QFile m_file;
    QBuffer m_input;
    QBuffer m_output;
    QByteArray m_data;
    QAudioDecoder m_decoder;
    QAudioFormat m_format;

    State m_state;

    bool isInited;
    bool isDecodingFinished;

    void clear();

private slots:
    void bufferReady();
    void finished();

    void onError(QAudioDecoder::Error error);

signals:
    void stateChanged(AudioFileStream::State state);
    void newData(const QByteArray& data);
};

#endif // AUDIOFILESTREAM_H