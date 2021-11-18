#include <QCoreApplication>
#include <QDebug>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "device/server/serverdevicediscoverymanager.h"
#include "value/server/servervaluemanager.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/server/systemtimemanager.h"
#include "warn/systemwarningsmanager.h"
#include "datamodel/server/datamodelmanager.h"
#include "processor/server/modelprocessormanager.h"
#include "actor/server/actormanager.h"
#include "log/logmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << Q_FUNC_INFO;

    QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false\nprocessor.*=true\ndatamodel.*=true"));

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::SERVER);

    QMqttCommunicationManager commManager;
    ServerDeviceDiscoveryManager deviceDiscoveryManager;
    ServerValueManager valueManager;
    ControllerManager controllerManager;
    SystemtimeManager systimeManager;
    SystemWarningsManager syswarnManager;
    DatamodelManager datamodelManager;
    ModelProcessorManager modelProcessor;
    LogManager logManager;
    ActorManager actorManager;

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&deviceDiscoveryManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&modelProcessor);
    managerRegistration.registerManager(&logManager);
    managerRegistration.registerManager(&actorManager);

    managerRegistration.init(&config);

    return a.exec();
}
