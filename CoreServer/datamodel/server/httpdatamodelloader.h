#ifndef HTTPDATAMODELLOADER_H
#define HTTPDATAMODELLOADER_H

#include <QObject>
#include <QUrl>
#include "datamodelloaderbase.h"

class HttpDataModelLoader : public DatamodelLoaderBase
{
    Q_OBJECT
public:
    explicit HttpDataModelLoader(QUrl url, QObject *parent = nullptr);

    static QString LOADER_TYPE_NAME;

    /*virtual*/ DatamodelBase* load() override;

    /*virtual*/ bool save(DatamodelBase* datamodel) override;

    /*virtual*/ QString typeName() override;

private:
    QUrl m_url;

signals:

public slots:
};

#endif // HTTPDATAMODELLOADER_H
