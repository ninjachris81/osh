#include "datamodelmanager.h"

#include <QDebug>

#include "datamodel/server/httpdatamodelloader.h"
#include "datamodel/server/testdatamodelloader.h"
#include "datamodel/server/filedatamodelloader.h"
#include "value/server/servervaluemanager.h"
#include "actor/actormanager.h"
#include "datamodel/server/emptydatamodel.h"

#include "macros.h"

QLatin1String DatamodelManager::MANAGER_ID = QLatin1String("DatamodelManager");

DatamodelManager::DatamodelManager(QObject *parent) : ManagerBase(parent)
{
    m_datamodel = new EmptyDatamodel();
}

LogCat::LOGCAT DatamodelManager::logCat() {
    return LogCat::DATAMODEL;
}

void DatamodelManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ValueManagerBase);
    REQUIRE_MANAGER(ActorManager);

    QString datamodelLoaderName = config->getString("datamodel.loader", TestDatamodelLoader::LOADER_TYPE_NAME);

    if (datamodelLoaderName == HttpDataModelLoader::LOADER_TYPE_NAME) {
        m_datamodelLoader = new HttpDataModelLoader(QUrl(config->getString("datamodel.url", "http://localhost/datamodel")));
    } else if (datamodelLoaderName == FileDataModelLoader::LOADER_TYPE_NAME) {
        m_datamodelLoader = new FileDataModelLoader(config->getString("datamodel.filePath", "datamodel.json"));
    } else if (datamodelLoaderName == TestDatamodelLoader::LOADER_TYPE_NAME) {
        m_datamodelLoader = new TestDatamodelLoader();
    } else {
        iWarning() << "Unknown datamodel loader" << datamodelLoaderName;
    }

    Q_ASSERT(m_datamodelLoader != nullptr);

    connect(m_datamodelLoader, &DatamodelLoaderBase::saved, this, &DatamodelManager::onDatamodelSaved);
    connect(m_datamodelLoader, &DatamodelLoaderBase::error, this, &DatamodelManager::onDatamodelError);

    delete m_datamodel;
    m_datamodel = m_datamodelLoader->load();
    Q_ASSERT(m_datamodel != nullptr);

    m_isLoaded = true;

    iDebug() << "Datamodel loaded";

    Q_EMIT(datamodelChanged());

    registerValues();

    registerActors();
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
        actorManager->registerActor(it.value());
        valueManager->registerValue(it.value());
    }
}

QString DatamodelManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE DatamodelManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void DatamodelManager::handleReceivedMessage(MessageBase* msg) {
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
