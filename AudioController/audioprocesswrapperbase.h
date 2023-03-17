#ifndef AUDIOPROCESSWRAPPERBASE_H
#define AUDIOPROCESSWRAPPERBASE_H

#include <QProcess>
#include <QMap>

class AudioProcessWrapperBase : public QProcess {
    Q_OBJECT

public:
    struct DeviceMapping {
        QString m_deviceId;
        int m_c;
        int m_channelIndex = 0;

        DeviceMapping() {
        }
        DeviceMapping(QString deviceId, int c, int channelIndex) : m_deviceId(deviceId), m_c(c), m_channelIndex(channelIndex) {
        }
    };

    AudioProcessWrapperBase(QString deviceId, QObject *parent = nullptr);

    void setVolume(float volume);

protected:
    QString m_deviceId;

    QMap<QString, DeviceMapping> m_cardMap;

};

#endif // AUDIOPROCESSWRAPPERBASE_H
