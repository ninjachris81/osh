#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "kmtronicrelaycontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "actor/client/clientactormanager.h"
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
    ClientActorManager actorManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_AC);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);

    KMTronicRelayController relayController(&controllerManager, config.getString(&clientManager, "inputValueGroupId", "egRelays0"), KMTronicRelayController::USB_SERIAL_8PORT, KMTronicRelayController::getRelayCount(KMTronicRelayController::USB_SERIAL_8PORT));
    controllerManager.registerController(&relayController);

    managerRegistration.init(&config);

    QList<ValueBase*> actors;
    ValueGroup actorGroup(relayController.id());
    for (quint8 i=0;i<KMTronicRelayController::getRelayCount(KMTronicRelayController::USB_SERIAL_8PORT);i++) {
        qDebug() << "Init actor" << i;
        DigitalActor* actor = new DigitalActor(&actorGroup, QString::number(i), VT_RELAY_LIGHT , true);
        actor->withValueTimeout(ValueBase::VT_NONE); // no need, as internal status update triggers maintainance
        actors.append(actor);
        relayController.bindActor(actor);
        actorManager.registerActor(actor);
    }

    relayController.bindValueManager(&valueManager, actors);

    controllerManager.start();

    return a.exec();
}
