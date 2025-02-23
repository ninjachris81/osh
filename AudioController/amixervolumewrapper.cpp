#include "amixervolumewrapper.h"
#include <QDebug>
#include <QProcess>

AMixerVolumeWrapper::AMixerVolumeWrapper(QObject *parent) : QObject(parent) {

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

    /*
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
    */

}

void AMixerVolumeWrapper::init() {
    for (quint8 cardId = 0; cardId < 255; cardId++) {
        QStringList args;

        args << "-c" << QString::number(cardId);
        args << "info";

        QString res = executeAmixer(args);

        qDebug() << Q_FUNC_INFO << res;

        if (res.isEmpty() || res.startsWith("Invalid card number")) {
            qDebug() << "Max reached";
            m_maxCardId--;
            break;
        } else {
            m_maxCardId++;
        }
    }

    qDebug() << "Max card id" << m_maxCardId;
}

bool AMixerVolumeWrapper::searchMapping(const QString deviceId) {
    QString devId = deviceId;
    if (deviceId.endsWith("_sv")) {
        devId = deviceId.chopped(3);
    }

    for (quint8 cardId = 0; cardId <= m_maxCardId; cardId++) {
        int mapping = _searchMapping(cardId, devId);
        if (mapping != -1) {
            qInfo() << "Adding mapping" << devId << cardId << mapping;
            addMapping(devId, cardId, mapping);
            return true;
        }
    }

    return false;
}

int AMixerVolumeWrapper::_searchMapping(quint8 cardId, const QString volumeId) {
    qDebug() << Q_FUNC_INFO << cardId << volumeId;

    QStringList args;

    args << "-c" << QString::number(cardId);
    args << "controls";

    QString res = executeAmixer(args);

    qDebug() << Q_FUNC_INFO << res;

    QStringList lines = res.split("\n", QString::SkipEmptyParts);
    for (QString line : lines) {
        QStringList tokens = line.split(",", QString::SkipEmptyParts);

        qDebug() << Q_FUNC_INFO << tokens;

        if (!tokens.isEmpty()) {
            if (tokens.size() == 3 && tokens[0].startsWith("numid=")) {
                quint8 id = tokens[0].mid(tokens[0].indexOf("=")+1).toInt();
                qDebug() << id << tokens[2].remove("Playback Volume").remove("name='").remove("'").trimmed();
                if (tokens[2].remove("Playback Volume").remove("name='").remove("'").trimmed() == volumeId) {
                    return id;
                }
            } else {
                qWarning() << "Unexpected tokens" << tokens;
            }
        } else {
            qWarning() << "Unexpected output line" << line;
        }
    }

    return -1;
}

QString AMixerVolumeWrapper::executeAmixer(const QStringList args) {
    QProcess proc;
    proc.setProgram("/usr/bin/amixer");
    proc.setArguments(args);
    proc.setProcessChannelMode(QProcess::MergedChannels);

    qInfo() << proc.program() << proc.arguments();

    proc.start();
    if (!proc.waitForFinished(1000)) {
        qWarning() << "AMixer did not finish in time";
    } else {
        return proc.readAllStandardOutput();
    }

    return "";
}

void AMixerVolumeWrapper::addMapping(const QString deviceId, int card, int numid) {
    qInfo() << Q_FUNC_INFO << deviceId << card << numid;

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
        deviceId = deviceId.chopped(3);
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
