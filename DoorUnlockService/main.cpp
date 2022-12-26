#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "doorunlock_controller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "actor/actormanager.h"
#include "doorunlock/doorunlockmanager.h"
#include "database/databasemanager.h"
#include "user/usermanager.h"
#include "actor/digitalactor.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("DoorUnlockService");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    ActorManager actorManager;
    DoorUnlockManager doorUnlockManager;
    DatabaseManager databaseManager;
    UserManager userManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_AC << MQTT_MESSAGE_TYPE_DU);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);
    managerRegistration.registerManager(&doorUnlockManager);
    managerRegistration.registerManager(&userManager);
    managerRegistration.registerManager(&databaseManager);

    DoorUnlockController frontDoorUnlockController(&controllerManager, "frontDoorUnlockController");
    controllerManager.registerController(&frontDoorUnlockController);

    managerRegistration.init(&config);

    QList<ValueBase*> actors;
    ValueGroup actorGroup(frontDoorUnlockController.id());
    DoorActor* frontDoorDoorActor = new DoorActor(&actorGroup, config.getString(&frontDoorUnlockController, "doorId", "frontDoor"), VALTYPE_DOOR_OPENER, true);
    DigitalActor* frontDoorRelayActor = new DigitalActor(&actorGroup, config.getString(&frontDoorUnlockController, "relayId", "frontDoorRelay"), value::VALTYPE_RELAY_DOOR_OPEN, true);

    actors.append(frontDoorDoorActor);
    actors.append(frontDoorRelayActor);

    actorManager.registerActor(frontDoorDoorActor);
    actorManager.registerActor(frontDoorRelayActor);

    frontDoorUnlockController.bindDoorActor(frontDoorDoorActor, frontDoorRelayActor);

    frontDoorUnlockController.bindValueManager(&valueManager, actors);

    controllerManager.start();

    return a.exec();
}
