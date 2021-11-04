#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "kmtronicrelaycontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration;

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceManager clientManager;
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager clientValueManager;

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&clientValueManager);

    KMTronicRelayController relayController(&controllerManager, "rc0", KMTronicRelayController::USB_SERIAL_8PORT, KMTronicRelayController::getRelayCount(KMTronicRelayController::USB_SERIAL_8PORT));
    controllerManager.registerController(&relayController);

    managerRegistration.init(&config);

    return a.exec();
}
