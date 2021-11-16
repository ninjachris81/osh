#include "httpdatamodelloader.h"

#include <QDebug>
#include "dynamicdatamodel.h"

QString HttpDataModelLoader::LOADER_TYPE_NAME = QStringLiteral("http");

HttpDataModelLoader::HttpDataModelLoader(QUrl url, QObject *parent) : DatamodelLoaderBase (parent), m_url(url)
{

}

DatamodelBase* HttpDataModelLoader::load() {
    iDebug() << Q_FUNC_INFO;

    return new DynamicDatamodel();
}

QString HttpDataModelLoader::typeName() {
    return LOADER_TYPE_NAME;
}
