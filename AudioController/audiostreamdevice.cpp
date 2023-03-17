#include "audiostreamdevice.h"
#include "qdebug.h"

AudioStreamDevice::AudioStreamDevice(QUrl url, QObject *parent)
    : QIODevice{parent}, m_url(url)
{

}


bool AudioStreamDevice::open(OpenMode mode) {
    QIODevice::open(mode);
    return true;
}

void AudioStreamDevice::close() {
    qDebug() << Q_FUNC_INFO;
    QIODevice::close();
}

qint64 AudioStreamDevice::readData(char *data, qint64 maxlen) {
    return 0;
}
