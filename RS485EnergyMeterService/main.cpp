#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "rs485energymetercontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "database/databasemanager.h"
#include "datamodel/datamodelmanager.h"
#include "log/logmanager.h"
#include "actor/actormanager.h"
#include "actor/digitalactor.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("EnergyMeterService");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    DatabaseManager databaseManager;
    DatamodelManager datamodelManager(false, false, false, true, false, false);
    ActorManager actorManager;
    LogManager logManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);

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

    RS485EnergyMeterController energyMeterController(&controllerManager, config.getString(&clientManager, "inputValueGroupId", "energyMeter0"));
    controllerManager.registerController(&energyMeterController);

    managerRegistration.init(&config);

    energyMeterController.bindValueManager(&valueManager, datamodelManager.datamodel());

    return a.exec();
}
