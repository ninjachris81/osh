#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
//#include "actor/actormanager.h"
#include "audiocontroller.h"
#include "actor/digitalactor.h"
#include "value/booleanvalue.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("AudioService");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);

    AudioController audioController(&controllerManager, config.getString(&clientManager, "audioGroupId", "egAudio0"));
    controllerManager.registerController(&audioController);

    managerRegistration.init(&config);

    QList<ValueBase*> values;

    ValueGroup actorGroup(audioController.id());
    for (quint8 i=0;i<audioController.channelCount();i++) {
        qDebug() << "Init value" << i;
        BooleanValue* value = new BooleanValue(&actorGroup, QString::number(i), VALTYPE_SWITCH);
        value->withValueTimeout(ValueBase::VT_MID);
        values.append(value);
        audioController.bindValue(value);
    }

    audioController.bindValueManager(&valueManager, values);
    audioController.bindCommunicationManager(&commManager);

    audioController.start();

    return a.exec();
}
