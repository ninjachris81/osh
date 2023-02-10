#include <QCoreApplication>
#include <QLoggingCategory>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "obiscontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "actor/actormanager.h"
#include "value/doublevalue.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    //QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false"));

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("OBISService");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    ActorManager actorManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);

    OBISController obisController(&controllerManager, config.getString(&clientManager, "inputValueGroupId", "obis"));
    controllerManager.registerController(&obisController);

    managerRegistration.init(&config);

    QList<ValueBase*> values;
    ValueGroup valueGroup(obisController.id());
    for (quint8 i=0;i<OBISController::SML_INDEX::COUNT;i++) {
        DoubleValue* value = new DoubleValue(&valueGroup, QString::number(i), value::VALTYPE_ENERGY_CONSUMPTION_TIME);
        value->withValueTimeout(ValueBase::VT_MID); // no need, as internal status update triggers maintainance
        values.append(value);
        obisController.bindValue(value);
        valueManager.registerValue(value);
    }

    qDebug() << "RUNNING";

    return a.exec();
}
