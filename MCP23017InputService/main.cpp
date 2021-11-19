#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "mcp23017inputcontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
//#include "actor/client/clientactormanager.h"
#include "actor/digitalactor.h"
#include "value/booleanvalue.h"

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

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);

    MCP23017InputController inputController(&controllerManager, "egInputs0");
    controllerManager.registerController(&inputController);

    managerRegistration.init(&config);

    QList<ValueBase*> values;

    ValueGroup actorGroup(inputController.id());
    for (quint8 i=0;i<inputController.inputCount();i++) {
        qDebug() << "Init value" << i;
        BooleanValue* value = new BooleanValue(&actorGroup, QString::number(i));
        values.append(value);
        inputController.bindValue(value);
    }

    inputController.bindValueManager(&valueManager, values);

    return a.exec();
}
