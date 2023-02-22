#ifndef TESTDATAMODELLOADER_H
#define TESTDATAMODELLOADER_H

#include <QObject>
#include "datamodelloaderbase.h"

class TestDatamodelLoader : public DatamodelLoaderBase
{
    Q_OBJECT
public:
    explicit TestDatamodelLoader(QObject *parent = nullptr);

    static QString LOADER_TYPE_NAME;

    /*virtual*/ DatamodelBase* load(ProcessorTaskFactory *processorTaskFactory, DatamodelLoadingOptions options) override;

    /*virtual*/ void save(DatamodelBase* datamodel) override;

    /*virtual*/ QString typeName() override;

signals:

public slots:
};

#endif // TESTDATAMODELLOADER_H
