#ifndef DATAMODELLOADERBASE_H
#define DATAMODELLOADERBASE_H

#include <QObject>
#include "datamodel/server/datamodelbase.h"

#include "identifyable.h"

class DatamodelLoaderBase : public Identifyable
{
    Q_OBJECT
public:
    explicit DatamodelLoaderBase(QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    virtual DatamodelBase* load() = 0;

    virtual void save(DatamodelBase* datamodel) = 0;

    virtual QString typeName() = 0;

signals:
    void saved();
    void error(QString desc);

public slots:
};

#endif // DATAMODELLOADERBASE_H
