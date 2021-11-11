#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "kmtronicrelaycontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "actor/client/clientactormanager.h"
#include "actor/digitalactor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration;

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceManager clientManager;
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    ClientActorManager actorManager;

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);

    KMTronicRelayController relayController(&controllerManager, "rc0", KMTronicRelayController::USB_SERIAL_8PORT, KMTronicRelayController::getRelayCount(KMTronicRelayController::USB_SERIAL_8PORT));
    controllerManager.registerController(&relayController);

    managerRegistration.init(&config);

    QList<DigitalActor*> actors;
    ValueGroup actorGroup(clientManager.device()->id());
    for (quint8 i=0;i<KMTronicRelayController::getRelayCount(KMTronicRelayController::USB_SERIAL_8PORT);i++) {
        qDebug() << "Init actor" << i;
        DigitalActor* actor = new DigitalActor(&actorGroup, QString::number(i), true);
        actors.append(actor);
        relayController.bindActor(actor, i);
        actorManager.registerActor(actors.value(i));
    }

    relayController.bindValueManager(&valueManager);

    return a.exec();
}
