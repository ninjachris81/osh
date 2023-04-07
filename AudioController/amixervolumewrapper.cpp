#include "amixervolumewrapper.h"
#include <QDebug>
#include <QProcess>

AMixerVolumeWrapper::AMixerVolumeWrapper(QObject *parent) : QObject(parent) {

    // some hard-coded stuff now...

    // amixer -c X controls
    addMapping("all_mono_mono", 0, 38);
    addMapping("all_mono_stereo", 0, 37);

    addMapping("mono3_0", 1, 11);
    addMapping("mono3_1", 1, 12);

    addMapping("mono0_0", 2, 11);
    addMapping("mono0_1", 2, 12);

    addMapping("mono4_0", 3, 11);
    addMapping("mono4_1", 3, 12);

    addMapping("mono1_0", 4, 11);
    addMapping("mono1_1", 4, 12);

    // 5 is hdmi

    addMapping("mono5_0", 6, 11);
    addMapping("mono5_1", 6, 12);

    addMapping("mono2_0", 7, 11);
    addMapping("mono2_1", 7, 12);

    addMapping("mono6_0", 8, 11);
    addMapping("mono6_1", 8, 12);

}

void AMixerVolumeWrapper::addMapping(QString deviceId, int card, int numid) {
    DeviceMapping mapping;
    mapping.deviceId = deviceId;
    mapping.card = card;
    mapping.numid = numid;

    m_cardMap.insert(deviceId, mapping);
}

void AMixerVolumeWrapper::setVolume(AudioPlaybackActor *audioActor) {
    QStringList args;

    QString deviceId = audioActor->audioDeviceIds().at(0);

    if (m_cardMap.contains(deviceId)) {
        int cardId = m_cardMap.value(deviceId).card;
        int numid = m_cardMap.value(deviceId).numid;

        int volumeInt = audioActor->audioVolume() * 100;      // range 0...1 -> 0...100
        QString volumeStr = QString::number(volumeInt) + "%";

        qDebug() << "amixer" << cardId << numid << volumeStr;

        args << "-c" << QString::number(cardId);
        args << "cset" ;
        args << "numid=" + QString::number(numid);
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
