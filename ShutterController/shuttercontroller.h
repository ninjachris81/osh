#ifndef SHUTTERCONTROLLER_H
#define SHUTTERCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QQueue>
#include <QMutex>

#include "actor/actormanager.h"
#include "actor/digitalactor.h"
#include "actor/shutteractor.h"
#include "sharedlib.h"
#include "controller/controllerbase.h"

class SHARED_LIB_EXPORT ShutterController : public ControllerBase
{
    Q_OBJECT

public:

#define SHUTTER_STATE_OPENED 0
#define SHUTTER_STATE_CLOSED 100

    enum ShutterState {
        ShutterInitializing,
        ShutterUp,
        ShutterDown,
        ShutterMovingUp,
        ShutterMovingDown
    };

    struct ActiveShutterMovement {
        ShutterActor *shutterActor;
        DigitalActor* relayActor;
        ACTOR_CMDS originalCmd;
        qint64 startedAt;
        qint64 duration;
        bool directionDown;
        bool isInit;
        bool isTilt;
    };

    ShutterController(ControllerManager* manager, ActorManager *actorManager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindActor(ShutterActor *shutterActor, DigitalActor* relayActorUp, DigitalActor* relayActorDown);

public slots:
    void onCmdTriggered(ACTOR_CMDS cmd);

private slots:
    void onMaintenance();

private:
    const float m_halfFactor = 2.2;         // 2.2 because duration has additional time
    void initializeShutters();

    void insertShutterMovements(ShutterActor* shutterActor, ACTOR_CMDS cmd, bool isInit = false);
    void insertShutterMovement(ShutterActor* shutterActor, ACTOR_CMDS originalCmd, qint64 duration, bool directionDown, bool isInit, bool isTilt);
    bool checkShutterInitMovements(ShutterActor* shutterActor, ACTOR_CMDS cmd);

    ValueManagerBase *m_valueManager;

    QMap<ShutterActor*, DigitalActor*> m_actorsUp;
    QMap<ShutterActor*, DigitalActor*> m_actorsDown;

    QMutex m_activeShutterMovementsMutex;
    QQueue<ActiveShutterMovement> m_activeShutterMovements;

    ActorManager *m_actorManager;
    QTimer m_maintenanceTimer;
};

#endif // SHUTTERCONTROLLER_H
