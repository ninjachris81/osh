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
        qint64 startedAt;
        qint64 duration;
        bool directionDown;
        bool updatesStatus;
        bool isInit;
    };

    ShutterController(ControllerManager* manager, ActorManager *actorManager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindActor(ShutterActor *shutterActor, DigitalActor* relayActorUp, DigitalActor* relayActorDown);

public slots:
    void onCmdTriggered(actor::ACTOR_CMDS cmd);

private slots:
    void onMaintenance();

private:
    void initializeShutters();

    void insertShutterMovements(ShutterActor* shutterActor, actor::ACTOR_CMDS cmd, bool isInit = false);
    void insertShutterMovement(ShutterActor* shutterActor, DigitalActor *relayActor, qint64 duration, bool directionDown, bool updatesStatus, bool isInit);
    bool cancelShutterMovements(ShutterActor* shutterActor);

    QMap<ShutterActor*, DigitalActor*> m_actorsUp;
    QMap<ShutterActor*, DigitalActor*> m_actorsDown;

    QMutex m_activeShutterMovementsMutex;
    QQueue<ActiveShutterMovement> m_activeShutterMovements;

    ActorManager *m_actorManager;
    QTimer m_maintenanceTimer;
};

#endif // SHUTTERCONTROLLER_H
