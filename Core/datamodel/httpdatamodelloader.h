#ifndef HTTPDATAMODELLOADER_H
#define HTTPDATAMODELLOADER_H

#include <QObject>
#include <QUrl>

#include "sharedlib.h"

#include "datamodelloaderbase.h"

class SHARED_LIB_EXPORT HttpDataModelLoader : public DatamodelLoaderBase
{
    Q_OBJECT
public:
    explicit HttpDataModelLoader(QUrl url, int requestTimeoutMs = 5000, QObject *parent = nullptr);

    static QString LOADER_TYPE_NAME;

    /*virtual*/ DatamodelBase* load(ProcessorTaskFactory *processorTaskFactory, DatamodelLoadingOptions options) override;

    /*virtual*/ void save(DatamodelBase* datamodel) override;

    /*virtual*/ QString typeName() override;

private:
    QUrl m_url;
    int m_requestTimeoutMs;

signals:

public slots:
};

#endif // HTTPDATAMODELLOADER_H
