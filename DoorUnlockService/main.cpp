#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "doorunlock_controller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "actor/client/clientactormanager.h"
#include "actor/digitalactor.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("WBB12Service");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    ClientActorManager actorManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_AC);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);

    DoorUnlockController doorUnlockController(&controllerManager, config.getString(&clientManager, "doorUnlockId", "frontDoor"));
    controllerManager.registerController(&doorUnlockController);

    managerRegistration.init(&config);

    controllerManager.start();

    return a.exec();
}
