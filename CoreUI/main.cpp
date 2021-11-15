#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "manager/managerregistration.h"
#include "device/devicediscoverymanagerui.h"
#include "qmqttcommunicationmanager.h"
#include "controller/controllermanager.h"
#include "datamodel/server/datamodelmanager.h"
#include "value/valuemanagerui.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::GUI);

    DeviceDiscoveryManagerUI deviceDiscoveryManager;
    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    DatamodelManager datamodelManager;
    ValueManagerUI valueManager;

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&deviceDiscoveryManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&valueManager);

    managerRegistration.init(&config);

    // register types
    qmlRegisterType<DeviceBaseUI>("OSH", 1, 0, "Device");
    qmlRegisterSingletonType<DeviceDiscoveryManagerUI>("OSH", 1, 0, "DeviceDiscoveryManager", &DeviceDiscoveryManagerUI::qmlInstance);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
