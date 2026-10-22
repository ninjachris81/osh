#include <QCoreApplication>
#include <QCommandLineParser>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "watermetercontroller.h"
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
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addPositionalArgument("config", "Configuration");
    parser.process(app);

    LocalConfig config(parser.positionalArguments().value(0, "config.ini"));

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("WaterMeterService");
    QStringList valueGroups;
    valueGroups << config.getString(&clientManager, "inputSensorGroupId", "");
    valueGroups << config.getString(&clientManager, "waterFlowValueGroupId", "");
    valueGroups << config.getString(&clientManager, "waterLevelValueGroupId", "");

    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    DatabaseManager databaseManager;
    DatamodelManager datamodelManager(false, false, false, true, false, false, false, QStringList(), valueGroups);
    LogManager logManager;

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&logManager);

    WaterMeterController waterLevelController(&controllerManager, valueGroups.at(2), valueGroups.at(0), valueGroups.at(1), valueGroups.at(2));
    controllerManager.registerController(&waterLevelController);

    managerRegistration.init(&config);

    waterLevelController.bindValueManager(&valueManager, datamodelManager.datamodel());

    managerRegistration.start();

    return app.exec();
}
