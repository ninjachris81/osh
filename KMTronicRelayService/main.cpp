#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "kmtronicrelaycontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "database/databasemanager.h"
#include "datamodel/datamodelmanager.h"
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
    QString valueGroup = config.getString(&clientManager, "inputValueGroupId", "allRelays0");

    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    DatabaseManager databaseManager;
    DatamodelManager datamodelManager(false, false, true, true, false, false, false, QStringList() << DigitalActor::staticMetaObject.className(), QStringList() << valueGroup);
    ActorManager actorManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);
    commManager.setCustomValueGroups(QStringList() << valueGroup);
    commManager.setCustomActorValueGroups(QStringList() << valueGroup);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&actorManager);

    KMTronicRelayController relayController(&controllerManager, valueGroup, KMTronicRelayController::USB_SERIAL_8PORT, KMTronicRelayController::getRelayCount(KMTronicRelayController::USB_SERIAL_8PORT));
    controllerManager.registerController(&relayController);

    managerRegistration.init(&config);

    ValueGroup *actorGroup = datamodelManager.datamodel()->valueGroup(relayController.id());
    Q_ASSERT(actorGroup != nullptr);

    for (quint8 i=0;i<KMTronicRelayController::getRelayCount(KMTronicRelayController::USB_SERIAL_8PORT);i++) {
        qDebug() << "Init actor" << actorGroup->id() << i;
        DigitalActor* actor = static_cast<DigitalActor*>(actorManager.getActor(actorGroup, QString::number(i)));
        Q_ASSERT(actor != nullptr);
        relayController.bindActor(actor);
    }

    return a.exec();
}
