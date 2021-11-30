#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "manager/managerregistration.h"
#include "device/devicediscoverymanagerui.h"
#include "qmqttcommunicationmanager.h"
#include "controller/controllermanager.h"
#include "datamodel/server/datamodelmanager.h"
#include "value/valuemanagerui.h"
#include "actor/server/actormanager.h"
#include "datamodel/datamodelmanagerui.h"
#include "processor/modelprocessormanagerui.h"
#include "log/logmanagerui.h"
#include "time/client/clientsystemtimemanager.h"

#define QML_BASE_PACKAGE "OSH"
#define QML_VERSION_MAJOR 1
#define QML_VERSION_MINOR 0

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    LocalConfig config;

    QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false\nvalue.*=true\ndatamodel.*=true\ncommunication.*=true"));

    ManagerRegistration managerRegistration(ManagerRegistration::GUI);

    DeviceDiscoveryManagerUI deviceDiscoveryManager("CoreUI");
    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    DatamodelManagerUI datamodelManager;
    ValueManagerUI valueManager;
    ActorManager actorManager;
    ModelProcessorManagerUI modelProcessorManager;
    LogManagerUI logManager;
    ClientSystemtimeManager systimeManager;

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&deviceDiscoveryManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);
    managerRegistration.registerManager(&modelProcessorManager);
    managerRegistration.registerManager(&logManager);
    managerRegistration.registerManager(&systimeManager);

    managerRegistration.init(&config);

    // register types

    qmlRegisterType<DeviceBaseUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "Device");
    qmlRegisterSingletonType<DeviceDiscoveryManagerUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "DeviceDiscoveryManager", &DeviceDiscoveryManagerUI::qmlInstance);
    qmlRegisterSingletonType<DatamodelManagerUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "DatamodelManager", &DatamodelManagerUI::qmlInstance);
    qmlRegisterSingletonType<ModelProcessorManagerUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "ModelProcessorManager", &ModelProcessorManagerUI::qmlInstance);
    qmlRegisterSingletonType<LogManagerUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "LogManager", &LogManagerUI::qmlInstance);

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
