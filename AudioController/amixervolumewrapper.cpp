#include "amixervolumewrapper.h"
#include <QDebug>
#include <QProcess>

AMixerVolumeWrapper::AMixerVolumeWrapper(QObject *parent) : QObject(parent) {

    addMapping("mono0_0_sv", 1, 0);
    addMapping("mono0_1_sv", 1, 1);

    addMapping("mono1_0_sv", 2, 0);
    addMapping("mono1_1_sv", 2, 1);

    addMapping("mono2_0_sv", 3, 0);
    addMapping("mono2_1_sv", 3, 1);
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
            volumeStr.append(",");
        } else {
            volumeStr.prepend(",");
        }

        qDebug() << "amixer" << cardId << volumeStr;

        args << "-c" << QString::number(cardId);
        args << "cset" << "name='Speaker Playback Volume'";
        args << volumeStr;

        QProcess proc;
        proc.setProgram("/usr/bin/amixer");
        proc.setArguments(args);
        proc.start();
        if (!proc.waitForFinished(1000)) {
            qWarning() << "AMixer did not finish in time";
        }
    } else {
        qWarning() << "Cannot find device mapping" << deviceId;
    }
}
