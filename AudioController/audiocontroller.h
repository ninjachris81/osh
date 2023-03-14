#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <QObject>
#include <QList>
#include <QProcess>
#include <QMutex>

#include "actor/actormanager.h"
#include "datamodel/datamodelbase.h"
#include "sharedlib.h"

#include "controller/audiocontrollerbase.h"
#include "actor/audioplaybackactor.h"
#include "communication/communicationmanagerbase.h"

class SHARED_LIB_EXPORT AudioController : public AudioControllerBase
{
    Q_OBJECT
public:
    struct AudioProcess {
        AudioPlaybackActor* actor;
        QProcess* process;
    };

    explicit AudioController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    void loadAudioActors(DatamodelBase *datamodel);

    void startPlayback(AudioPlaybackActor *audioActor) override;
    void pausePlayback(AudioPlaybackActor *audioActor) override;
    void stopPlayback(AudioPlaybackActor *audioActor) override;

    void executeActivation(AudioPlaybackActor *audioActor, bool activate);

private:
    ValueGroup *m_audioGroup;

    QString m_playbackCmd;

    CommunicationManagerBase* m_commManager;
    ActorManager *m_actorManager;

    bool validatePlaybackUrl(QString url);

protected slots:
    void onStartPlayback();
    void onPausePlayback();
    void onStopPlayback();

signals:

protected:
    QMap<AudioPlaybackActor*, DigitalActor*> m_actorRelayMappings;

    QMap<QString, AudioProcess> m_playbackProcesses;
    QMutex m_playbackProcessMutex;

};

#endif // AUDIOCONTROLLER_H
