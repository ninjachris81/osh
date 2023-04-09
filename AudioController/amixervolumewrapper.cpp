#include "amixervolumewrapper.h"
#include <QDebug>
#include <QProcess>

AMixerVolumeWrapper::AMixerVolumeWrapper(QObject *parent) : QObject(parent) {

    // some hard-coded stuff now...

    /*
    0_0 vz
    0_1 wc

    1_0 ez
    1_1 k

    2_0 az
    2_1 feg

    3_0 fog
    3_1 b

    4_0 sz
    4_1 uz

    5_0 wz1
    5_1 wz2

    6_0 hfo
    6_1 hfe
    */


    // amixer -c X controls
    addMapping("all_mono_mono", 0, 38);
    addMapping("all_mono_stereo", 0, 37);

    addMapping("mono0_0", 1, 11);
    addMapping("mono0_1", 1, 12);

    addMapping("mono1_0", 2, 11);
    addMapping("mono1_1", 2, 12);

    addMapping("mono2_0", 3, 12);
    addMapping("mono2_1", 3, 13);

    addMapping("mono3_0", 4, 12);
    addMapping("mono3_1", 4, 13);

    addMapping("mono4_0", 5, 11);
    addMapping("mono4_1", 5, 12);

    // 6 is hdmi

    addMapping("mono5_0", 7, 11);
    addMapping("mono5_1", 7, 12);


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
    if (deviceId.endsWith("_sv")) {
        deviceId.chop(3);
    }

    if (m_cardMap.contains(deviceId)) {
        int cardId = m_cardMap.value(deviceId).card;
        int numid = m_cardMap.value(deviceId).numid;

        int volumeInt = audioActor->audioVolume() * 100;      // range 0...1 -> 0...100

        args << "-c" << QString::number(cardId);
        args << "cset" ;
        args << "numid=" + QString::number(numid);
        args << QString::number(volumeInt) + "%";

        QProcess proc;
        proc.setProgram("/usr/bin/amixer");
        proc.setArguments(args);

        qInfo() << proc.program() << proc.arguments();

        proc.start();
        if (!proc.waitForFinished(1000)) {
            qWarning() << "AMixer did not finish in time";
        }
    } else {
        qWarning() << "Cannot find device mapping" << deviceId;
    }
}
