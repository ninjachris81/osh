#include "filedatamodelloader.h"

#include <QFile>

#include "dynamicdatamodel.h"

QString FileDataModelLoader::LOADER_TYPE_NAME = QStringLiteral("file");

FileDataModelLoader::FileDataModelLoader(QString filePath, QObject *parent) : DatamodelLoaderBase(parent), m_filePath(filePath)
{

}

DatamodelBase *FileDataModelLoader::load(DatamodelLoadingOptions options) {
    iDebug() << Q_FUNC_INFO;

    QFile file(m_filePath);
    if (!file.exists()) {
        iWarning() << "Creating new empty datamodel";
        DynamicDatamodel* datamodel = new DynamicDatamodel();
        return datamodel;
    } else if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        DynamicDatamodel* datamodel = new DynamicDatamodel();
        datamodel->deserialize(data);

        return datamodel;
    } else {
        iWarning() << "Can only load dynamic datamodels";
        Q_EMIT(error("Can only load dynamic datamodels"));
    }
    return nullptr;
}

QString FileDataModelLoader::typeName() {
    return LOADER_TYPE_NAME;
}


void FileDataModelLoader::save(DatamodelBase* datamodel) {
    DynamicDatamodel* dynDatamodel = qobject_cast<DynamicDatamodel*>(datamodel);
    if (dynDatamodel != nullptr) {
        QByteArray data = dynDatamodel->serialize();

        QFile file(m_filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(data);
            file.close();
            Q_EMIT(saved());
        } else {
            iWarning() << "Unable to open file " << m_filePath;
            Q_EMIT(error("Unable to open file"));
        }
    } else {
        iWarning() << "Can only save dynamic datamodels";
        Q_EMIT(error("Can only save dynamic datamodels"));
    }
}
