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
#include "datamodel/server/datamodelmanager.h"
#include "processor/server/modelprocessormanager.h"
#include "actor/server/actormanager.h"
#include "log/logmanager.h"
#include "database/databasemanager.h"

//  not sure why this block is needed to compile in 5.12
#include "value/longvalue.h"
#include "value/stringvalue.h"
#include "actor/audioplaybackactor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << Q_FUNC_INFO;

    //  not sure why this block is needed to compile in 5.12
    KnownDevice test1;
    ValueGroup test2;
    ShutterActor test3;
    IntegerValue test4;
    DoubleValue test5;
    LongValue test6;
    StringValue test7;
    AudioPlaybackActor test8;
    DigitalActor test9;
    BooleanValue test10;


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
    DatamodelManager datamodelManager;
    ModelProcessorManager modelProcessor;
    LogManager logManager;
    ActorManager actorManager;
    DatabaseManager databaseManager;

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
    managerRegistration.registerManager(&databaseManager);

    managerRegistration.init(&config);

    return a.exec();
}
