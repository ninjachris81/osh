#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "wbb12controller.h"
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
    ClientDeviceDiscoveryManager clientManager("WBB12Service");
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

    WBB12Controller wbb12Controller(&controllerManager, config.getString(&clientManager, "inputValueGroupId", "wbb12"));
    controllerManager.registerController(&wbb12Controller);

    managerRegistration.init(&config);

    wbb12Controller.bindValueManager(&valueManager);

    /*
    QList<ValueBase*> actors;
    ValueGroup actorGroup(relayController.id());
    for (quint8 i=0;i<RS485RelayController::getRelayCount(RS485RelayController::RS485_SERIAL_32PORT);i++) {
        qDebug() << "Init actor" << i;
        DigitalActor* actor = new DigitalActor(&actorGroup, QString::number(i), VALTYPE_RELAY_LIGHT , true);
        actor->withValueTimeout(ValueBase::VALTYPE_NONE); // no need, as internal status update triggers maintainance
        actors.append(actor);
        relayController.bindActor(actor);
        actorManager.registerActor(actor);
    }

    relayController.bindValueManager(&valueManager, actors);
    */

    return a.exec();
}
