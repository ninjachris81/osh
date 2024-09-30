#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "database/databasemanager.h"
#include "datamodel/datamodelmanager.h"
#include "shuttercontroller.h"
#include "actor/actormanager.h"
#include "log/logmanager.h"
#include "actor/shutteractor.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("ShutterService");
    QString valueGroup = config.getString(&clientManager, "shutterValueGroupId", "allShutters0");
    QString relayValueGroupId = config.getString(valueGroup, "relayValueGroupId", "allRelays0");

    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    DatabaseManager databaseManager;
    DatamodelManager datamodelManager(false, false, true, true, false, false, false, QStringList() << ShutterActor::staticMetaObject.className() << DigitalActor::staticMetaObject.className(), QStringList() << valueGroup << relayValueGroupId);
    ClientValueManager valueManager;
    ActorManager actorManager;
    LogManager logManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);
    commManager.setCustomValueGroups(QStringList() << valueGroup << relayValueGroupId);
    commManager.setCustomActorValueGroups(QStringList() << valueGroup << relayValueGroupId);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&logManager);

    ShutterController shutterController(&controllerManager, &actorManager, valueGroup);
    controllerManager.registerController(&shutterController);

    managerRegistration.init(&config);

    qInfo() << "Init shutter group" << valueGroup;
    ValueGroup *shutterGroup = datamodelManager.datamodel()->valueGroup(valueGroup);
    Q_ASSERT(shutterGroup != nullptr);
    quint16 shutterOffset = config.getInt(shutterGroup, "shutterValueGroupOffset", 0);

    qInfo() << "Init relay group" << relayValueGroupId;
    ValueGroup *relayGroup = datamodelManager.datamodel()->valueGroup(relayValueGroupId);
    Q_ASSERT(relayGroup != nullptr);
    quint16 relayOffset = config.getInt(shutterGroup, "relayValueGroupOffset", 0);
    quint16 count = config.getInt(shutterGroup, "shutterCount", 1);

    for (quint8 i=0;i<count;i++) {
        qDebug() << i + shutterOffset;
        ShutterActor* shutterActor = static_cast<ShutterActor*>(actorManager.getActor(shutterGroup, QString::number(i + shutterOffset)));
        Q_ASSERT(shutterActor != nullptr);
        qInfo() << "Init actor" << i << shutterActor->fullId();
        qDebug() << (i * 2) + relayOffset;
        DigitalActor* relayActorUp = static_cast<DigitalActor*>(actorManager.getActor(relayGroup, QString::number((i * 2) + relayOffset)));
        Q_ASSERT(relayActorUp != nullptr);
        qInfo() << "Init actor relay up" << relayActorUp->fullId();
        qDebug() << (i * 2) + relayOffset + 1;
        DigitalActor* relayActorDown = static_cast<DigitalActor*>(actorManager.getActor(relayGroup, QString::number((i * 2) + relayOffset + 1)));
        Q_ASSERT(relayActorDown != nullptr);
        qInfo() << "Init actor relay down" << relayActorDown->fullId();
        shutterController.bindActor(shutterActor, relayActorUp, relayActorDown);
    }

    return a.exec();
}
