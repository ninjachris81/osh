#include "simulator.h"

Simulator::Simulator(LocalConfig *config, QObject *parent) : QObject(parent), m_config(config)
{

    m_managerRegistration = new ManagerRegistration(ManagerRegistration::SERVER);

    m_commManager = new QMqttCommunicationManager();
    m_deviceDiscoveryManager = new ServerDeviceDiscoveryManager("CoreServerSimulator");
    m_valueManager = new ServerValueManager();
    m_controllerManager = new ControllerManager();
    m_systimeManager = new SystemtimeManagerSimulator();
    m_syswarnManager = new SystemWarningsManager();
    m_datamodelManager = new DatamodelManager(true, true, true, true, true, true);
    m_modelProcessor = new ModelProcessorManager();
    m_logManager = new LogManager();
    m_actorManager = new ActorManager();
    m_databaseManager = new DatabaseManager();

    m_managerRegistration->registerManager(m_commManager);
    m_managerRegistration->registerManager(m_deviceDiscoveryManager);
    m_managerRegistration->registerManager(m_valueManager);
    m_managerRegistration->registerManager(m_controllerManager);
    m_managerRegistration->registerManager(m_systimeManager);
    m_managerRegistration->registerManager(m_syswarnManager);
    m_managerRegistration->registerManager(m_datamodelManager);
    m_managerRegistration->registerManager(m_modelProcessor);
    m_managerRegistration->registerManager(m_logManager);
    m_managerRegistration->registerManager(m_actorManager);
    m_managerRegistration->registerManager(m_databaseManager);
}

void Simulator::init() {
    qInfo() << Q_FUNC_INFO;

    m_managerRegistration->init(m_config);
}
