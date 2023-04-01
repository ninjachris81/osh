#include <QCoreApplication>
#include <QDebug>

#include "actor/actorbase.h"
#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "device/server/serverdevicediscoverymanager.h"
#include "value/server/servervaluemanager.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/server/systemtimemanager.h"
#include "warn/systemwarningsmanager.h"
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

    qDebug() << Q_FUNC_INFO;

    //QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false\nprocessor.*=true\ndatamodel.*=true"));
    //QLoggingCategory::setFilterRules(QStringLiteral("device.*=false"));

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::SERVER);

    QMqttCommunicationManager commManager;
    ServerDeviceDiscoveryManager deviceDiscoveryManager("CoreServer");
    ServerValueManager valueManager;
    ControllerManager controllerManager;
    SystemtimeManager systimeManager;
    SystemWarningsManager syswarnManager;
    DatamodelManager datamodelManager(true, true, true, true, true, true, true);
    ModelProcessorManager modelProcessor;
    datamodelManager.setProcessorTaskFactory(&modelProcessor);
    LogManager logManager;
    ActorManager actorManager;
    DatabaseManager databaseManager;
    SimpleDatabaseManager simpleDatabaseManager;

    ToggleController toggleController(&controllerManager, "ToggleController");

    controllerManager.registerController(&toggleController);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&deviceDiscoveryManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&actorManager);
    managerRegistration.registerManager(&modelProcessor);
    managerRegistration.registerManager(&logManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&simpleDatabaseManager);

    managerRegistration.init(&config);

    toggleController.bindManager(&actorManager, &valueManager);

    return a.exec();
}
