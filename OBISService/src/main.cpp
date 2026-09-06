#include <QCoreApplication>
#include <QLoggingCategory>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "obiscontroller2.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "database/databasemanager.h"
#include "datamodel/datamodelmanager.h"
#include "log/logmanager.h"
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
    ClientDeviceDiscoveryManager clientManager("EnergyMeterService");
    QString valueGroup = config.getString(&clientManager, "inputValueGroupId", "obis");

    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    DatabaseManager databaseManager;
    DatamodelManager datamodelManager(false, false, false, true, false, false, false, QStringList(), QStringList() << valueGroup);
    LogManager logManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);
    commManager.setCustomValueGroups(QStringList() << valueGroup);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&databaseManager);
    managerRegistration.registerManager(&datamodelManager);
    managerRegistration.registerManager(&logManager);

    OBISController2 obisController(&controllerManager, valueGroup);
    controllerManager.registerController(&obisController);

    managerRegistration.init(&config);

    qInfo() << "Init value group" << obisController.id();
    ValueGroup *valueGroupObj = datamodelManager.datamodel()->valueGroup(obisController.id());
    Q_ASSERT(valueGroupObj != nullptr);

    for (quint8 i=0;i<OBISController2::SML_INDEX::COUNT;i++) {
        DoubleValue* value = static_cast<DoubleValue*>(valueManager.getValue(valueGroupObj, QString::number(i)));
        Q_ASSERT(value != nullptr);
        obisController.bindValue(value);
    }

    return a.exec();
}
