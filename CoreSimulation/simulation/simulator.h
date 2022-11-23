#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>

#include "sharedlib.h"

#include "actor/actorbase.h"
#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "device/server/serverdevicediscoverymanager.h"
#include "value/server/servervaluemanager.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/server/systemtimemanagersimulator.h"
#include "warn/systemwarningsmanager.h"
#include "datamodel/server/datamodelmanager.h"
#include "processor/server/modelprocessormanager.h"
#include "actor/server/actormanager.h"
#include "log/logmanager.h"
#include "database/databasemanager.h"

class SHARED_LIB_EXPORT Simulator : public QObject
{
    Q_OBJECT
public:
    explicit Simulator(LocalConfig* config, QObject *parent = nullptr);

protected:
    LocalConfig* m_config;

    ManagerRegistration* m_managerRegistration;

    QMqttCommunicationManager* m_commManager;
    ServerDeviceDiscoveryManager* m_deviceDiscoveryManager;
    ServerValueManager* m_valueManager;
    ControllerManager* m_controllerManager;
    SystemtimeManagerSimulator* m_systimeManager;
    SystemWarningsManager* m_syswarnManager;
    DatamodelManager* m_datamodelManager;
    ModelProcessorManager* m_modelProcessor;
    LogManager* m_logManager;
    ActorManager*  m_actorManager;
    DatabaseManager* m_databaseManager;

signals:

};

#endif // SIMULATOR_H
