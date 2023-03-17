#include "audioprocesswrapperbase.h"
#include "qdebug.h"
#include <QtMath>

AudioProcessWrapperBase::AudioProcessWrapperBase(QString deviceId, QObject *parent) : QProcess(parent), m_deviceId(deviceId) {

    m_cardMap.insert("mono0_0", DeviceMapping("mono0_0", 1, 0));
    m_cardMap.insert("mono0_1", DeviceMapping("mono0_1", 1, 1));

    m_cardMap.insert("mono1_0", DeviceMapping("mono1_0", 2, 0));
    m_cardMap.insert("mono1_1", DeviceMapping("mono1_1", 2, 1));

    m_cardMap.insert("mono2_0", DeviceMapping("mono2_0", 3, 0));
    m_cardMap.insert("mono2_1", DeviceMapping("mono2_1", 3, 1));

    Q_ASSERT(m_cardMap.contains(m_deviceId));
}

void AudioProcessWrapperBase::setVolume(float volume) {
    QStringList args;

    if (m_cardMap.contains(m_deviceId)) {
        // some hard-coded stuff now...
        int cardId = m_cardMap.value(m_deviceId).m_c;

        int volumeInt = volume * 100;      // range 0...1 -> 0...100
        QString volumeStr = QString::number(volumeInt) + "%";

        if (m_cardMap.value(m_deviceId).m_channelIndex == 0) {
            volumeStr.prepend(",");
        } else {
            volumeStr.append(",");
        }

        qDebug() << "amixer" << cardId << volumeStr;

        args << "-c" << QString::number(cardId);
        args << "cset" << "name='Speaker Playback Volume'";
        args << volumeStr;

        QProcess::execute("/usr/bin/amixer", args);
    } else {
        qWarning() << "Cannot find device mapping" << m_deviceId;
    }
}
