#ifndef DOORCAMERA_CONTROLLER_H
#define DOORCAMERA_CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QProcess>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "actor/actormanager.h"
#include "doorunlock/doorunlockmanager.h"
#include "actor/dooractor.h"
#include "actor/digitalactor.h"

class SHARED_LIB_EXPORT DoorCameraController : public ControllerBase
{
    Q_OBJECT
public:
    explicit DoorCameraController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindDoorRingActor(DigitalActor *doorRingActor);

protected slots:
    void onRingTriggered(actor::ACTOR_CMDS cmd);

private:
    void startRecording();

    DigitalActor *m_doorRingActor;
    ClientSystemWarningsManager* m_warnManager;
    ValueManagerBase* m_valueManager;
    ActorManager* m_actorManager;

    QString m_program;
    int m_duration = 20;
    QString rtspUrl = "";
    QString baseStorageUrl = "";


signals:

};

#endif // DOORCAMERA_CONTROLLER_H
