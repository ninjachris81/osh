#include <QCoreApplication>
#include <QDebug>

#include "actor/actorbase.h"
#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "user/usermanager.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "datamodel/datamodelmanager.h"
#include "processor/server/modelprocessormanager.h"
#include "actor/actormanager.h"
#include "log/logmanager.h"
#include "database/databasemanager.h"
#include "database/simpledatabasemanager.h"
#include "actor/server/togglecontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("ScriptingTestService");

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    ClientDeviceDiscoveryManager deviceDiscoveryManager("ScriptingTestServer");
    ClientValueManager valueManager;
    DatamodelManager datamodelManager(true, true, true, true, true, true, true);
    ModelProcessorManager modelProcessor;
    datamodelManager.setProcessorTaskFactory(&modelProcessor);
    LogManager logManager;
    ActorManager actorManager;
    DatabaseManager databaseManager;
    SimpleDatabaseManager simpleDatabaseManager;
    UserManager userManager;

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&deviceDiscoveryManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&actorManager);
    managerRegistration.registerManager(&modelProcessor);
    managerRegistration.registerManager(&logManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&simpleDatabaseManager);
    managerRegistration.registerManager(&userManager);

    managerRegistration.init(&config);

    return a.exec();
}
