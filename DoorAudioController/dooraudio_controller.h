#ifndef DOORAUDIO_CONTROLLER_H
#define DOORAUDIO_CONTROLLER_H

#include <QObject>
#include <QTimer>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "actor/actormanager.h"
#include "doorunlock/doorunlockmanager.h"
#include "actor/dooractor.h"
#include "actor/digitalactor.h"

#include "oshaccount.h"
#include "oshendpoint.h"

class SHARED_LIB_EXPORT DoorAudioController : public ControllerBase
{
    Q_OBJECT
public:
    explicit DoorAudioController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindDoorRingActor(DigitalActor *doorRingActor);

protected slots:
    void onRingTriggered(actor::ACTOR_CMDS cmd);

public slots:
    void onCallStateChanged(int state);

private:
    OshEndpoint m_endpoint;
    OshAccount *m_account;
    QString m_sipRingId;

    DigitalActor *m_doorRingActor;
    ClientSystemWarningsManager* m_warnManager;
    ValueManagerBase* m_valueManager;
    ActorManager* m_actorManager;


signals:

};

#endif // DOORAUDIO_CONTROLLER_H
