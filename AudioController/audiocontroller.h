#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <QObject>
#include <QList>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QMutex>

#include "actor/actormanager.h"
#include "audiooutputwrapper.h"
#include "datamodel/datamodelbase.h"
#include "qaudiodeviceinfo.h"
#include "sharedlib.h"

#include "controller/audiocontrollerbase.h"
#include "actor/audioplaybackactor.h"
#include "communication/communicationmanagerbase.h"

class SHARED_LIB_EXPORT AudioController : public AudioControllerBase
{
    Q_OBJECT
public:
    explicit AudioController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    void loadAudioActors(DatamodelBase *datamodel, ClientValueManager *valueManager);

    void startPlayback(AudioPlaybackActor *audioActor) override;
    void pausePlayback(AudioPlaybackActor *audioActor) override;
    void stopPlayback(AudioPlaybackActor *audioActor) override;

    void executeActivation(AudioPlaybackActor *audioActor, bool activate);

private:
    ValueGroup *m_audioGroup;
    QMutex m_mutex;

    CommunicationManagerBase* m_commManager;
    ActorManager *m_actorManager;

    QMap<QString, QAudioDeviceInfo> m_availableDeviceInfos;

    QMap<QString, AudioOutputWrapper*> m_audioOutputs;
    QMultiMap<AudioPlaybackActor*, AudioOutputWrapper*> m_audioOutputMappings;
    //QMap<QString, QIODevice*> m_audioDevices;
    //QMap<QString, AudioPlaybackActor*> m_audioActors;

    void initAvailableDevices();
    void initDevice(QString deviceName, AudioPlaybackActor *playbackActor);

    void _start(AudioPlaybackActor *audioActor, QIODevice *device, QAudioOutput *output);
    void _stop(AudioPlaybackActor *audioActor);

protected slots:
    void onStartPlayback();
    void onPausePlayback();
    void onStopPlayback();
    void onVolumeChanged();

    void onNext();
    void onPrevious();

signals:

protected:
    QMap<AudioPlaybackActor*, DigitalActor*> m_actorRelayMappings;

};

#endif // AUDIOCONTROLLER_H
