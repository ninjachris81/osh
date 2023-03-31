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
    DatamodelManager datamodelManager(false, false, true, true, false, false, QStringList() << DigitalActor::staticMetaObject.className());

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

    DoorAudioController doorAudioController(&controllerManager, "frontDoorAudioController");
    controllerManager.registerController(&doorAudioController);

    managerRegistration.init(&config);

    DigitalActor* doorRingActor = static_cast<DigitalActor*>(datamodelManager.datamodel()->actor(config.getString(&doorAudioController, "doorRingActorId", "ring0")));
    Q_ASSERT(doorRingActor != nullptr);

    doorAudioController.bindDoorRingActor(doorRingActor);

    return a.exec();
}
