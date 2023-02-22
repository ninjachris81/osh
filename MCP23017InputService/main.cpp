#include <QCoreApplication>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "mcp23017inputcontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "database/databasemanager.h"
#include "datamodel/datamodelmanager.h"
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
    DatabaseManager databaseManager;
    DatamodelManager datamodelManager(false, false, false, true, false, false);
    ClientValueManager valueManager;
    LogManager logManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&logManager);

    MCP23017InputController inputController(&controllerManager, config.getString(&clientManager, "inputValueGroupId", "switches"));
    managerRegistration.init(&config);

    qInfo() << "Init value group" << inputController.id();
    ValueGroup *valueGroup = datamodelManager.datamodel()->valueGroup(inputController.id());
    Q_ASSERT(valueGroup != nullptr);

    quint16 offset = config.getInt(valueGroup, "inputValueGroupOffset", 0);
    controllerManager.registerController(&inputController);

    for (quint8 i=offset;i<inputController.inputCount() + offset;i++) {
        qDebug() << "Init value" << valueGroup->id() << i;
        BooleanValue* value = static_cast<BooleanValue*>(valueManager.getValue(valueGroup, QString::number(i)));
        Q_ASSERT(value != nullptr);
        inputController.bindValue(value);
    }

    return a.exec();
}
