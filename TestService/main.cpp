#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include "qmqttcommunicationmanager.h"
#include "log/logmanager.h"
#include "manager/managerregistration.h"
#include "device/client/clientdevicemanager.h"
#include "controller/controllermanager.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addPositionalArgument("config", "Configuration");
    parser.process(app);

    LocalConfig config(parser.positionalArguments().value(0, "config.ini"));

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("TestService");
    LogManager logManager;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&logManager);

    QTimer timeoutTimer;
    QObject::connect(&timeoutTimer, &QTimer::timeout, [&app] () {
        app.exit();
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

    return app.exec();
}
