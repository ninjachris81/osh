#ifndef DATAMODELLOADERBASE_H
#define DATAMODELLOADERBASE_H

#include <QObject>

#include "sharedlib.h"

#include "datamodel/datamodelbase.h"
#include "processor/processortaskfactory.h"
#include "identifyable.h"

class SHARED_LIB_EXPORT DatamodelLoaderBase : public QObject, public Identifyable
{
    Q_OBJECT
public:
    struct DatamodelLoadingOptions {
        bool loadKnownAreas = true;
        bool loadKnownRooms = true;
        bool loadActors = true;
        bool loadValues = true;
        bool loadProcessorTasks = true;
        bool loadKnownDevices = true;
    };

    explicit DatamodelLoaderBase(QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    virtual DatamodelBase* load(ProcessorTaskFactory *processorTaskFactory, DatamodelLoadingOptions options) = 0;

    virtual void save(DatamodelBase* datamodel) = 0;

    virtual QString typeName() = 0;

signals:
    void saved();
    void error(QString desc);

public slots:
};

#endif // DATAMODELLOADERBASE_H
