#include "datamodelmanager.h"

#include <QDebug>
#include "httpdatamodelloader.h"
#include "testdatamodelloader.h"
#include "value/valuemanager.h"

#include "macros.h"

QString DatamodelManager::MANAGER_NAME = QStringLiteral("DatamodelManager");

DatamodelManager::DatamodelManager(QObject *parent) : ManagerBase(parent)
{
}

void DatamodelManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ValueManager);

    QString datamodelLoaderName = config->getString("datamodel.loader", TestDatamodelLoader::LOADER_TYPE_NAME);

    if (datamodelLoaderName == HttpDataModelLoader::LOADER_TYPE_NAME) {
        m_datamodelLoader = new HttpDataModelLoader(QUrl(config->getString("datamodel.url", "http://localhost/datamodel")));
    } else if (datamodelLoaderName == TestDatamodelLoader::LOADER_TYPE_NAME) {
        m_datamodelLoader = new TestDatamodelLoader();
    } else {
        qWarning() << "Unknown datamodel loader" << datamodelLoaderName;
    }

    Q_ASSERT(m_datamodelLoader != nullptr);

    m_datamodel = m_datamodelLoader->load();

    Q_ASSERT(m_datamodel != nullptr);

    ValueManager* valueManager = getManager<ValueManager>(ValueManager::MANAGER_NAME);

    QListIterator<ValueBase*> it(m_datamodel->values());
    while (it.hasNext()) {
        valueManager->registerValue(it.next());
    }
}

QString DatamodelManager::getName() {
    return MANAGER_NAME;
}

MessageBase::MESSAGE_TYPE DatamodelManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void DatamodelManager::handleReceivedMessage(MessageBase* msg) {
}
