#ifndef AMIXERVOLUMEWRAPPER_H
#define AMIXERVOLUMEWRAPPER_H

#include <QObject>
#include <QMap>

#include "actor/audioplaybackactor.h"

class SHARED_LIB_EXPORT AMixerVolumeWrapper : public QObject
{
    Q_OBJECT

public:
    struct DeviceMapping {
        QString deviceId;
        int c;
        int channelIndex = 0;
    };

    explicit AMixerVolumeWrapper(QObject *parent = nullptr);

    void setVolume(AudioPlaybackActor *audioActor);

    void addMapping(QString deviceId, int c, int channelIndex);

protected:
    QMap<QString, DeviceMapping> m_cardMap;

signals:

};

#endif // AMIXERVOLUMEWRAPPER_H
