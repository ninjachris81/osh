#ifndef DATAMODELLOADERBASE_H
#define DATAMODELLOADERBASE_H

#include <QObject>
#include "datamodel/server/datamodelbase.h"

class DatamodelLoaderBase : public QObject
{
    Q_OBJECT
public:
    explicit DatamodelLoaderBase(QObject *parent = nullptr);

    virtual DatamodelBase* load() = 0;

    virtual QString typeName() = 0;

signals:

public slots:
};

#endif // DATAMODELLOADERBASE_H
