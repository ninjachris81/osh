#ifndef DOORUNLOCK_CONTROLLER_H
#define DOORUNLOCK_CONTROLLER_H

#include <QObject>
#include <QTimer>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "actor/actormanager.h"
#include "doorunlock/doorunlockmanager.h"
#include "actor/dooractor.h"
#include "actor/digitalactor.h"

#define UNLOCK_ENABLE_DURATION_MS 2000

class SHARED_LIB_EXPORT DoorUnlockController : public ControllerBase
{
    Q_OBJECT
public:
    explicit DoorUnlockController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindDoorActor(DoorActor* door, DigitalActor* relay);

protected slots:
    void onUnlockDoor(QString doorId);

private:
    DoorUnlockManager* m_doorUnlockManager;
    ClientSystemWarningsManager* m_warnManager;
    ActorManager* m_actorManager;

    DoorActor* m_door;
    DigitalActor* m_relay;


signals:

};

#endif // DOORUNLOCK_CONTROLLER_H
