#include <QCoreApplication>
#include <QDebug>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "device/devicediscoverymanager.h"
#include "value/valuemanager.h"
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

    ManagerRegistration managerRegistration;

    QMqttCommunicationManager commManager;
    DeviceDiscoveryManager deviceDiscoveryManager;
    ValueManager valueManager;
    ControllerManager controllerManager;
    ClientDeviceManager clientDeviceManager;
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
