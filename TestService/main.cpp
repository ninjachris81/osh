#include <QCoreApplication>
#include <QDebug>
#include "qmqttcommunicationmanager.h"
#include "log/logmanager.h"
#include "manager/managerregistration.h"
#include "device/client/clientdevicemanager.h"
#include "controller/controllermanager.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("TestService");
    LogManager logManager;

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&logManager);

    QTimer timeoutTimer;
    QObject::connect(&timeoutTimer, &QTimer::timeout, [&a] () {
        a.exit();
    });

    QObject::connect(&commManager, &QMqttCommunicationManager::isConnectedChanged, [&commManager, &timeoutTimer]() {
        if (commManager.isConnected()) {
            qDebug() << "Connected";

            ValueMessage valueMessage("test", "1", 123);
            commManager.sendMessage(valueMessage);

            timeoutTimer.start(20000);
        }
    });

    managerRegistration.init(&config);

    return a.exec();
}
