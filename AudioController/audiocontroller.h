#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <QObject>
#include <QList>
#include <QProcess>
#include "controller/audiocontrollerbase.h"
#include "actor/audioplaybackactor.h"
#include "communication/communicationmanagerbase.h"

class AudioController : public AudioControllerBase
{
    Q_OBJECT
public:
    explicit AudioController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ quint8 channelCount() override;

    void startPlayback(quint8 channelIndex) override;
    void pausePlayback(quint8 channelIndex) override;
    void stopPlayback(quint8 channelIndex) override;

    void bindCommunicationManager(CommunicationManagerBase *commManager);

private:
    QProcess m_playbackProcess;
    QString m_playbackCmd;
    QString m_playbackFile;

    CommunicationManagerBase* m_commManager;

signals:
    void requestActivation(QString amplGroupId, QString amplActorId, bool activate);

protected:
    quint8 m_actorCount = 0;
    QList<AudioPlaybackActor*> m_actorMappings;

};

#endif // AUDIOCONTROLLER_H
