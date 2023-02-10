#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "rs485relaycontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
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
    ActorManager actorManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_AC);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);

    RS485RelayController relayController(&controllerManager, config.getString(&clientManager, "inputValueGroupId", "allRelays0"), RS485RelayController::RS485_SERIAL_32PORT, RS485RelayController::getRelayCount(RS485RelayController::RS485_SERIAL_32PORT));
    quint16 offset = config.getInt(&clientManager, "inputValueGroupOffset", 0);
    controllerManager.registerController(&relayController);

    managerRegistration.init(&config);

    QList<ValueBase*> actors;
    ValueGroup actorGroup(relayController.id());
    for (quint8 i=offset;i<RS485RelayController::getRelayCount(RS485RelayController::RS485_SERIAL_32PORT) + offset;i++) {
        qDebug() << "Init actor" << i;
        DigitalActor* actor = new DigitalActor(&actorGroup, QString::number(i), VALTYPE_RELAY_LIGHT , true);
        actor->withValueTimeout(ValueBase::VT_NONE); // no need, as internal status update triggers maintainance
        actors.append(actor);
        relayController.bindActor(actor);
        actorManager.registerActor(actor, &valueManager);
    }

    return a.exec();
}
