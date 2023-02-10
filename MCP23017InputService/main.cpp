#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "mcp23017inputcontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "log/logmanager.h"
//#include "actor/actormanager.h"
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
    ClientDeviceDiscoveryManager clientManager("InputService");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    LogManager logManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&logManager);

    MCP23017InputController inputController(&controllerManager, config.getString(&clientManager, "inputValueGroupId", "switches"));
    quint16 offset = config.getInt(&clientManager, "inputValueGroupOffset", 0);
    controllerManager.registerController(&inputController);

    managerRegistration.init(&config);

    QList<ValueBase*> values;

    ValueGroup actorGroup(inputController.id());
    for (quint8 i=offset;i<inputController.inputCount() + offset;i++) {
        qDebug() << "Init value" << i;
        BooleanValue* value = new BooleanValue(&actorGroup, QString::number(i), VALTYPE_SWITCH);
        value->withValueTimeout(ValueBase::VT_MID);
        values.append(value);
        inputController.bindValue(value);
        valueManager.registerValue(value);
    }

    return a.exec();
}
