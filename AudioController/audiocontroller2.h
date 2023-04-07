#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <QObject>
#include <QList>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QMutex>
#include <QProcess>

#include "actor/actormanager.h"
#include "amixervolumewrapper.h"
#include "datamodel/datamodelbase.h"
#include "audioprocesswrapperbase.h"
#include "qaudiodeviceinfo.h"
#include "sharedlib.h"

#include "controller/audiocontrollerbase.h"
#include "actor/audioplaybackactor.h"
#include "communication/communicationmanagerbase.h"

class SHARED_LIB_EXPORT AudioController2 : public AudioControllerBase
{
    Q_OBJECT
public:
    explicit AudioController2(ControllerManager* manager, QString id, QObject *parent = nullptr);

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

    QMap<QString, AudioProcessWrapperBase*> m_runningProcesses;
    QMap<QString, AudioPlaybackActor*> m_playbackActors;

    CommunicationManagerBase* m_commManager;
    ActorManager *m_actorManager;
    ValueManagerBase *m_valueManager;
    AMixerVolumeWrapper m_volumeWrapper;

    void _start(AudioPlaybackActor *audioActor, QIODevice *device, QAudioOutput *output);
    void _stop(AudioPlaybackActor *audioActor);

    void stopProcess(QString audioActorId);
    void stopAllProcesses();

private slots:
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessError(QProcess::ProcessError error);
    void onCurrentTitleChanged(QString currentTitle);

protected slots:
    void onStartPlayback();
    void onPausePlayback();
    void onStopPlayback();
    void onVolumeChanged();
    void onUrlChanged();

    void onNext();
    void onPrevious();

signals:

protected:
    QMap<AudioPlaybackActor*, DigitalActor*> m_actorRelayMappings;

};

#endif // AUDIOCONTROLLER_H
