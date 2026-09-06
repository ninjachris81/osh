#pragma once

#include <QObject>
#include <QMap>

#include "actor/audioplaybackactor.h"

class SHARED_LIB_EXPORT AMixerVolumeWrapper : public QObject
{
    Q_OBJECT

public:
    struct DeviceMapping {
        QString deviceId;
        int card;
        int numid = 0;
    };

    explicit AMixerVolumeWrapper(QObject *parent = nullptr);

    void init();

    bool searchMapping(const QString deviceId);

    void setVolume(AudioPlaybackActor *audioActor);

private:
    int _searchMapping(quint8 cardId, const QString volumeId);

    void addMapping(const QString deviceId, int card, int numid);

    QString executeAmixer(const QStringList args);

protected:
    QMap<QString, DeviceMapping> m_cardMap;
    quint8 m_maxCardId = 0;

signals:

};

