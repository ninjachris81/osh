#include "audiofiledevice.h"

AudioFileDevice::AudioFileDevice(const QString &fileName, const QAudioFormat &format) :
    m_file(fileName),
    m_input(&m_data),
    m_output(&m_data)
{
    setOpenMode(QIODevice::ReadOnly);

    const bool valid =
        m_file.open(QIODevice::ReadOnly) &&
        m_output.open(QIODevice::ReadOnly) &&
        m_input.open(QIODevice::WriteOnly);

    Q_ASSERT(valid);

    m_decoder.setNotifyInterval(10);
    m_decoder.setAudioFormat(format);

    isDecodingFinished = false;

    connect(&m_decoder, SIGNAL(bufferReady()), this, SLOT(bufferReady()));
    connect(&m_decoder, SIGNAL(finished()), this, SLOT(finished()));
    connect(&m_decoder, SIGNAL(error(QAudioDecoder::Error)), this, SLOT(onError(QAudioDecoder::Error)));


    m_decoder.setSourceDevice(&m_file);
    m_decoder.start();
}

bool AudioFileDevice::open(OpenMode mode) {
    QIODevice::open(mode);
    return true;
}

// AudioOutput device (like speaker) call this function for get new audio data
qint64 AudioFileDevice::readData(char* data, qint64 maxlen)
{
    memset(data, 0, maxlen);

    m_output.read(data, maxlen);

    // There is we send readed audio data via signal, for ability get audio signal for the who listen this signal.
    // Other word this emulate QAudioProbe behaviour for retrieve audio data which of sent to output device (speaker).
    if (maxlen > 0)
    {
        QByteArray buff(data, maxlen);
        emit newData(buff);
    }

    return maxlen;
}

qint64 AudioFileDevice::writeData(const char* data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

void AudioFileDevice::clear()
{
    m_decoder.stop();
    m_data.clear();
    isDecodingFinished = false;
}

// Is finish of file
bool AudioFileDevice::atEnd() const
{
    return m_output.size()
        && m_output.atEnd()
        && isDecodingFinished;
}



/////////////////////////////////////////////////////////////////////
// QAudioDecoder logic this methods responsible for decode audio file and put audio data to stream buffer

// Run when decode decoded some audio data
void AudioFileDevice::bufferReady() // SLOT
{
    const QAudioBuffer &buffer = m_decoder.read();

    const int length = buffer.byteCount();
    const char *data = buffer.constData<char>();

    m_input.write(data, length);
}

// Run when decode finished decoding
void AudioFileDevice::finished() // SLOT
{
    isDecodingFinished = true;
}

void AudioFileDevice::onError(QAudioDecoder::Error error) {
    qDebug() << error;
}
