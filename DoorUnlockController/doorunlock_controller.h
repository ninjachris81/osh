#ifndef DOORUNLOCK_CONTROLLER_H
#define DOORUNLOCK_CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QMutex>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "actor/actormanager.h"
#include "value/valuemanagerbase.h"
#include "doorunlock/doorunlockmanager.h"
#include "actor/dooractor.h"
#include "actor/digitalactor.h"

class SHARED_LIB_EXPORT DoorUnlockController : public ControllerBase
{
    Q_OBJECT
public:
    explicit DoorUnlockController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindActors(DoorActor* doorActor, DigitalActor* relay);

protected slots:
    void onUnlockDoor(QString doorId);

private:
    void initRelay();
    void enableRelay(bool enable);

    DoorUnlockManager* m_doorUnlockManager;
    ClientSystemWarningsManager* m_warnManager;
    ActorManager* m_actorManager;
    ValueManagerBase *m_valueManager;

    int m_relayPin = 0;
    int relayEnableDurationMs = 2000;

    bool m_isUnlocking = false;
    QMutex unlockingMutex;

    QString m_doorId;

    DoorActor* m_door;
    DigitalActor* m_relay;


signals:

};

#endif // DOORUNLOCK_CONTROLLER_H
