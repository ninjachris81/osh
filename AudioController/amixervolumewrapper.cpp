#include "amixervolumewrapper.h"
#include <QDebug>
#include <QProcess>

AMixerVolumeWrapper::AMixerVolumeWrapper(QObject *parent) : QObject(parent) {

    addMapping("mono0_0", 1, 0);
    addMapping("mono0_1", 1, 1);

    addMapping("mono1_0", 2, 0);
    addMapping("mono1_1", 2, 1);

    addMapping("mono2_0", 3, 0);
    addMapping("mono2_1", 3, 1);
}

void AMixerVolumeWrapper::addMapping(QString deviceId, int c, int channelIndex) {
    DeviceMapping mapping;
    mapping.deviceId = deviceId;
    mapping.c = c;
    mapping.channelIndex = channelIndex;

    m_cardMap.insert(deviceId, mapping);
}

void AMixerVolumeWrapper::setVolume(AudioPlaybackActor *audioActor) {
    QStringList args;

    QString deviceId = audioActor->audioDeviceIds().at(0);

    if (m_cardMap.contains(deviceId)) {
        // some hard-coded stuff now...
        int cardId = m_cardMap.value(deviceId).c;

        int volumeInt = audioActor->audioVolume() * 100;      // range 0...1 -> 0...100
        QString volumeStr = QString::number(volumeInt) + "%";

        if (m_cardMap.value(deviceId).channelIndex == 0) {
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
        qWarning() << "Cannot find device mapping" << deviceId;
    }
}