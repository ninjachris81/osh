#ifndef FILEDATAMODELLOADER_H
#define FILEDATAMODELLOADER_H

#include <QObject>

#include "sharedlib.h"

#include "datamodelloaderbase.h"

class SHARED_LIB_EXPORT FileDataModelLoader : public DatamodelLoaderBase
{
    Q_OBJECT
public:
    explicit FileDataModelLoader(QString filePath, QObject *parent = nullptr);

    static QString LOADER_TYPE_NAME;

    /*virtual*/ DatamodelBase* load(ProcessorTaskFactory *processorTaskFactory, DatamodelLoadingOptions options) override;

    /*virtual*/ void save(DatamodelBase* datamodel) override;

    /*virtual*/ QString typeName() override;

private:
    QString m_filePath;

signals:

};

#endif // FILEDATAMODELLOADER_H
