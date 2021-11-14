#include <QCoreApplication>
#include <QDebug>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "device/server/devicediscoverymanagerserver.h"
#include "value/server/valuemanagerserver.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/systemtimemanager.h"
#include "warn/systemwarningsmanager.h"
#include "datamodel/datamodelmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << Q_FUNC_INFO;

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::SERVER);

    QMqttCommunicationManager commManager;
    DeviceDiscoveryManagerServer deviceDiscoveryManager;
    ValueManagerServer valueManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientDeviceManager;
    SystemtimeManager systimeManager;
    SystemWarningsManager syswarnManager;
    DatamodelManager datamodelManager;

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&deviceDiscoveryManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientDeviceManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&datamodelManager);

    managerRegistration.init(&config);

    return a.exec();
}
