#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "dooraudio_controller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "actor/actormanager.h"
#include "database/databasemanager.h"
#include "datamodel/datamodelmanager.h"
#include "actor/digitalactor.h"
#include "datamodel/datamodelmanager.h"
#include "log/logmanager.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("DoorAudioService");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    ActorManager actorManager;
    DatabaseManager databaseManager;
    DatamodelManager datamodelManager(false, false, true, true, false, false, false, QStringList() << DigitalActor::staticMetaObject.className());
    LogManager logManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_AC << MQTT_MESSAGE_TYPE_DU);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&logManager);

    DoorAudioController doorAudioController(&controllerManager, "frontDoorAudioController");
    controllerManager.registerController(&doorAudioController);

    managerRegistration.init(&config);

    DigitalActor* doorRingActor = static_cast<DigitalActor*>(actorManager.getActor(config.getString(&doorAudioController, "doorRingActorId", "frontDoor.ring")));
    Q_ASSERT(doorRingActor != nullptr);

    doorAudioController.bindDoorRingActor(doorRingActor);

    return a.exec();
}
