#ifndef FILEDATAMODELLOADER_H
#define FILEDATAMODELLOADER_H

#include <QObject>
#include "datamodelloaderbase.h"

class FileDataModelLoader : public DatamodelLoaderBase
{
    Q_OBJECT
public:
    explicit FileDataModelLoader(QString filePath, QObject *parent = nullptr);

    static QString LOADER_TYPE_NAME;

    /*virtual*/ DatamodelBase* load() override;

    /*virtual*/ void save(DatamodelBase* datamodel) override;

    /*virtual*/ QString typeName() override;

private:
    QString m_filePath;

signals:

};

#endif // FILEDATAMODELLOADER_H
