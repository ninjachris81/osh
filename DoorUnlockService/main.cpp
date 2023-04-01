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
#include "datamodel/datamodelmanager.h"
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
    DatamodelManager datamodelManager(false, false, true, true, false, false, true, QStringList() << DoorActor::staticMetaObject.className() << DigitalActor::staticMetaObject.className());
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
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&userManager);

    DoorUnlockController doorUnlockController(&controllerManager, "frontDoorUnlockController");
    controllerManager.registerController(&doorUnlockController);

    managerRegistration.init(&config);

    DoorActor* doorActor = static_cast<DoorActor*>(actorManager.getActor(config.getString(&doorUnlockController, "doorId", "frontDoor.door")));
    DigitalActor* doorRelayActor = static_cast<DigitalActor*>(actorManager.getActor(config.getString(&doorUnlockController, "relayId", "frontDoor.relay")));

    Q_ASSERT(doorActor != nullptr);
    Q_ASSERT(doorRelayActor != nullptr);

    doorUnlockController.bindActors(doorActor, doorRelayActor);

    return a.exec();
}
