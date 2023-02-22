#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "rs485relaycontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "database/databasemanager.h"
#include "datamodel/datamodelmanager.h"
#include "log/logmanager.h"
#include "actor/actormanager.h"
#include "actor/digitalactor.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("RelayService");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    DatabaseManager databaseManager;
    DatamodelManager datamodelManager(false, false, true, true, false, false);
    ActorManager actorManager;
    LogManager logManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_AC);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&actorManager);
    managerRegistration.registerManager(&logManager);

    managerRegistration.init(&config);

    RS485RelayController relayController(&controllerManager, config.getString(&clientManager, "inputValueGroupId", "allRelays0"), RS485RelayController::RS485_SERIAL_32PORT, RS485RelayController::getRelayCount(RS485RelayController::RS485_SERIAL_32PORT));
    quint16 offset = config.getInt(&clientManager, "inputValueGroupOffset", 0);
    controllerManager.registerController(&relayController);

    qInfo() << "Init actor group" << relayController.id();
    ValueGroup *actorGroup = datamodelManager.datamodel()->valueGroup(relayController.id());
    Q_ASSERT(actorGroup != nullptr);

    for (quint8 i=offset;i<RS485RelayController::getRelayCount(RS485RelayController::RS485_SERIAL_32PORT) + offset;i++) {
        qDebug() << "Init actor" << actorGroup->id() << i;
        DigitalActor* actor = static_cast<DigitalActor*>(actorManager.getActor(actorGroup, QString::number(i)));
        Q_ASSERT(actor != nullptr);
        relayController.bindActor(actor);
    }

    return a.exec();
}
