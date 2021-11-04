#include "testdatamodelloader.h"

#include <QDebug>
#include "testdatamodel.h"

QString TestDatamodelLoader::LOADER_TYPE_NAME = QStringLiteral("test");


TestDatamodelLoader::TestDatamodelLoader(QObject *parent) : DatamodelLoaderBase(parent)
{

}

DatamodelBase* TestDatamodelLoader::load() {
    qDebug() << Q_FUNC_INFO;
    return new TestDatamodel();
}

QString TestDatamodelLoader::typeName() {
    return LOADER_TYPE_NAME;
}
