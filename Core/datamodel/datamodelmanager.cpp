#include "datamodelmanager.h"

#include <QDebug>

#include "datamodel/httpdatamodelloader.h"
#include "datamodel/testdatamodelloader.h"
#include "datamodel/filedatamodelloader.h"
#include "actor/actormanager.h"
#include "datamodel/emptydatamodel.h"
#include "datamodel/dbdatamodelloader.h"

#include "macros.h"
#include "user/usermanager.h"
#include "value/valuemanagerbase.h"

QLatin1String DatamodelManager::MANAGER_ID = QLatin1String("DatamodelManager");

DatamodelManager::DatamodelManager(bool loadKnownAreas, bool loadKnownRooms, bool loadActors, bool loadValues, bool loadProcessorTasks, bool loadKnownDevices, bool loadUsers, QStringList actorClassTypeFilter, QStringList valueGroupFilter, QObject *parent) : ManagerBase(parent)
{
    m_loadingOptions.loadKnownAreas = loadKnownAreas;
    m_loadingOptions.loadKnownRooms = loadKnownRooms;
    m_loadingOptions.loadActors = loadActors;
    m_loadingOptions.loadValues = loadValues;
    m_loadingOptions.loadProcessorTasks = loadProcessorTasks;
    m_loadingOptions.loadKnownDevices = loadKnownDevices;
    m_loadingOptions.loadUsers = loadUsers;
    m_loadingOptions.actorClassTypeFilter = actorClassTypeFilter;
    m_loadingOptions.valueGroupFilter = valueGroupFilter;

    if (!actorClassTypeFilter.isEmpty() && !loadActors) {
        iWarning() << "Actor filter set, but actors not loaded";
        Q_ASSERT(false);
    }

    if (!valueGroupFilter.isEmpty() && (!loadValues && !loadActors)) {
        iWarning() << "Value Group filter set, but neither values or actors loaded";
        Q_ASSERT(false);
    }

    m_datamodel = new EmptyDatamodel();
}

LogCat::LOGCAT DatamodelManager::logCat() {
    return LogCat::DATAMODEL;
}

void DatamodelManager::setProcessorTaskFactory(ProcessorTaskFactory* processorTaskFactory) {
    m_processorTaskFactory = processorTaskFactory;
}

void DatamodelManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    if (m_loadingOptions.loadValues) {
        REQUIRE_MANAGER(ValueManagerBase);
    }
    if (m_loadingOptions.loadActors) {
        REQUIRE_MANAGER(ActorManager);
    }

    QString datamodelLoaderName = config->getString("datamodel.loader", TestDatamodelLoader::LOADER_TYPE_NAME);

    if (datamodelLoaderName == HttpDataModelLoader::LOADER_TYPE_NAME) {
        m_datamodelLoader = new HttpDataModelLoader(QUrl(config->getString("datamodel.url", "http://localhost/datamodel")));
    } else if (datamodelLoaderName == FileDataModelLoader::LOADER_TYPE_NAME) {
        m_datamodelLoader = new FileDataModelLoader(config->getString("datamodel.filePath", "datamodel.json"));
    } else if (datamodelLoaderName == TestDatamodelLoader::LOADER_TYPE_NAME) {
        m_datamodelLoader = new TestDatamodelLoader();
    } else if (datamodelLoaderName == DBDatamodelLoader::LOADER_TYPE_NAME) {
        REQUIRE_MANAGER(DatabaseManager);
        DatabaseManager* databaseManager = getManager<DatabaseManager>(DatabaseManager::MANAGER_ID);
        m_datamodelLoader = new DBDatamodelLoader(databaseManager);
    } else {
        iWarning() << "Unknown datamodel loader" << datamodelLoaderName;
    }

    Q_ASSERT(m_datamodelLoader != nullptr);

    connect(m_datamodelLoader, &DatamodelLoaderBase::saved, this, &DatamodelManager::onDatamodelSaved);
    connect(m_datamodelLoader, &DatamodelLoaderBase::error, this, &DatamodelManager::onDatamodelError);

    delete m_datamodel;
    m_datamodel = m_datamodelLoader->load(m_processorTaskFactory, m_loadingOptions);
    Q_ASSERT(m_datamodel != nullptr);

    // check for unreplaced vars
    for (ProcessorTaskBase *task : m_datamodel->processorTasks()) {
        for (QString param : task->paramList()) {
            if (param.contains(ProcessorVariable::VARIABLE_PREFIX)) {
                iWarning() << "Unreplaced processor variable in task" << task->id();
                Q_ASSERT(false);
            }
        }
    }

    m_isLoaded = true;

    iDebug() << "Datamodel loaded";

    // now, register values in managers
    if (m_loadingOptions.loadValues) {
        registerValues();
    }

    if (m_loadingOptions.loadActors) {
        registerActors();
    }

    if (m_loadingOptions.loadUsers) {
        registerUsers();
    }

    Q_EMIT(datamodelChanged());
}

void DatamodelManager::registerValues() {
    // register values
    ValueManagerBase* valueManager = getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    QMapIterator<QString, ValueBase*> it(m_datamodel->values());
    while (it.hasNext()) {
        it.next();
        iDebug() << "Register datamodel value" << it.key();
        valueManager->registerValue(it.value());
    }
}

void DatamodelManager::registerActors() {
    // register actors
    ActorManager* actorManager = getManager<ActorManager>(ActorManager::MANAGER_ID);
    ValueManagerBase* valueManager = getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    QMapIterator<QString, ActorBase*> it(m_datamodel->actors());
    while(it.hasNext()) {
        it.next();
        iDebug() << "Register datamodel actor" << it.key();
        actorManager->registerActor(it.value(), valueManager);
    }
}

void DatamodelManager::registerUsers() {
    // register actors
    UserManager* userManager = getManager<UserManager>(UserManager::MANAGER_ID);

    QMapIterator<QString, OshUser*> it(m_datamodel->users());
    while(it.hasNext()) {
        it.next();
        iDebug() << "Register user" << it.key();
        userManager->registerUser(it.value());
    }
}

QString DatamodelManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE DatamodelManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void DatamodelManager::handleReceivedMessage(MessageBase* msg) {
    Q_UNUSED(msg)
}

DatamodelBase* DatamodelManager::datamodel() {
    return m_datamodel;
}

bool DatamodelManager::isLoaded() {
    return m_isLoaded;
}

void DatamodelManager::onDatamodelSaved() {
    iDebug() << "Datamodel saved";
}

void DatamodelManager::onDatamodelError(QString desc) {
    iWarning() << "Error while saving datamodel" << desc;
}

void DatamodelManager::save() {
    iDebug() << Q_FUNC_INFO;

    m_datamodelLoader->save(m_datamodel);
}
