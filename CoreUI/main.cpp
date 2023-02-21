#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "manager/managerregistration.h"
#include "device/devicediscoverymanagerui.h"
#include "qmqttcommunicationmanager.h"
#include "controller/controllermanager.h"
#include "datamodel/datamodelmanager.h"
#include "value/valuemanagerui.h"
#include "actor/actormanager.h"
#include "datamodel/datamodelmanagerui.h"
#include "processor/modelprocessormanagerui.h"
#include "log/logmanagerui.h"
#include "time/client/clientsystemtimemanager.h"
#include "connectoritembase.h"

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

    qmlRegisterUncreatableMetaObject(unit::staticMetaObject, QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "UNIT_TYPE", "Enums cannot be instantiated");
    qRegisterMetaType<unit::UNIT_TYPE>("unit::UNIT_TYPE");

    qmlRegisterUncreatableMetaObject(value::staticMetaObject, QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "VALUE_TYPE", "Enums cannot be instantiated");
    qRegisterMetaType<value::VALUE_TYPE>("value::VALUE_TYPE");

    qmlRegisterUncreatableMetaObject(actor::staticMetaObject, QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "ACTOR_CMDS", "Enums cannot be instantiated");
    qRegisterMetaType<actor::ACTOR_CMDS>("actor::ACTOR_CMDS");

    qmlRegisterType<DeviceBaseUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "Device");
    qmlRegisterSingletonType<DeviceDiscoveryManagerUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "DeviceDiscoveryManager", &DeviceDiscoveryManagerUI::qmlInstance);
    qmlRegisterSingletonType<DatamodelManagerUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "DatamodelManager", &DatamodelManagerUI::qmlInstance);
    qmlRegisterSingletonType<ModelProcessorManagerUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "ModelProcessorManager", &ModelProcessorManagerUI::qmlInstance);
    qmlRegisterSingletonType<ValueManagerUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "ValueManager", &ValueManagerUI::qmlInstance);
    qmlRegisterSingletonType<LogManagerUI>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "LogManager", &LogManagerUI::qmlInstance);

    qmlRegisterType<ConnectorItemBase>(QML_BASE_PACKAGE, QML_VERSION_MAJOR, QML_VERSION_MINOR, "ConnectorItem");

    QQmlApplicationEngine engine;

    engine.addImportPath(":/qml");

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
