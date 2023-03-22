#include <QCoreApplication>

#include "actor/actormanager.h"
#include "database/databasemanager.h"
#include "datamodel/datamodelmanager.h"
#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "log/logmanager.h"
//#include "actor/actormanager.h"
//#include "audiocontroller.h"
#include "audiocontroller2.h"
#include "actor/digitalactor.h"
#include "value/booleanvalue.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("AudioService");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    DatabaseManager databaseManager;
    DatamodelManager datamodelManager(false, false, true, true, false, false, QStringList() << AudioPlaybackActor::staticMetaObject.className() << DigitalActor::staticMetaObject.className());
    ActorManager actorManager;
    LogManager logManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_VA  << MQTT_MESSAGE_TYPE_AC);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&actorManager);
    managerRegistration.registerManager(&logManager);

    QString audioGroupId = config.getString(&clientManager, "audioGroupId", "egAudio0");
    AudioController2 audioController(&controllerManager, audioGroupId);
    controllerManager.registerController(&audioController);

    managerRegistration.init(&config);

    audioController.loadAudioActors(datamodelManager.datamodel(), &valueManager);

    return a.exec();
}
