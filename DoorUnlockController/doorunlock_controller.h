#ifndef DOORUNLOCK_CONTROLLER_H
#define DOORUNLOCK_CONTROLLER_H

#include <QObject>
#include <QTimer>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"

class SHARED_LIB_EXPORT DoorUnlockController : public ControllerBase
{
    Q_OBJECT
public:
    explicit DoorUnlockController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

protected slots:

private:
    ClientSystemWarningsManager* m_warnManager;


signals:

};

#endif // DOORUNLOCK_CONTROLLER_H
