#ifndef AUDIOPLAYBACKACTOR_H
#define AUDIOPLAYBACKACTOR_H

#include <QObject>

#include "sharedlib.h"

#include "actorbase.h"
#include "value/doublevalue.h"
#include "value/stringvalue.h"

class SHARED_LIB_EXPORT AudioPlaybackActor : public ActorBase
{
    Q_OBJECT
public:
    static QLatin1String PROPERTY_AUDIO_DEVICE_IDS;
    static QLatin1String PROPERTY_AUDIO_ACTIVATION_RELAY_ID;
    static QLatin1String PROPERTY_AUDIO_VOLUME;
    static QLatin1String PROPERTY_AUDIO_VOLUME_ID;
    static QLatin1String PROPERTY_AUDIO_URL;
    static QLatin1String PROPERTY_AUDIO_URL_ID;
    static QLatin1String PROPERTY_AUDIO_CURRENT_TITLE_ID;

    enum AudioPlaybackState {
        STOPPED = 0,
        PLAYING = 1,
        PAUSED = 2,
        ERROR = 10
    };

    AudioPlaybackActor();
    explicit AudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, QString audioDeviceIds, QString audioActivationRelayId, float audioVolume, QString audioVolumeId, QString audioUrl, QString audioUrlId, QString audioCurrentTitleId, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(actor::ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

    AudioPlaybackActor* withAudioVolumeValue(DoubleValue* volume);

    AudioPlaybackActor* withAudioUrlValue(StringValue* url);

    AudioPlaybackActor* withAudioCurrentTitleValue(StringValue *currentTitle);

    AudioPlaybackState playbackState();
    void setPlaybackState(AudioPlaybackState state);

    QStringList audioDeviceIds();
    QString audioActivationRelayId();
    float audioVolume();
    QString audioVolumeId();
    QString audioUrl();
    QString audioUrlId();
    QString audioCurrentTitleId();
    StringValue *audioCurrentTitle();

protected:
    QStringList m_audioDeviceIds;
    QString m_audioActivationRelayId = "";
    float m_audioVolume = 1;
    QString m_audioVolumeId = "";
    QString m_audioUrl = "";
    QString m_audioUrlId = "";

    DoubleValue* m_audioVolumeValue = nullptr;
    StringValue* m_audioUrlValue = nullptr;
    StringValue* m_audioCurrentTitleValue = nullptr;

    /*virtual*/ void _triggerCmd(actor::ACTOR_CMDS cmd);

protected slots:
    void onVolumeChanged();
    void onUrlChanged();

signals:
    void startPlaybackRequested();
    void stopPlaybackRequested();
    void pausePlaybackRequested();

    void volumeChanged();
    void urlChanged();

    void nextRequested();
    void previousRequested();

public slots:
};

#endif // AUDIOPLAYBACKACTOR_H
