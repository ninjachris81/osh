#ifndef DBDATAMODELLOADER_H
#define DBDATAMODELLOADER_H

#include <QObject>
#include <QSqlResult>
#include "sharedlib.h"

#include "datamodelloaderbase.h"
#include "database/databasemanager.h"
#include "datamodel/dynamicdatamodel.h"

class DBDatamodelLoader : public DatamodelLoaderBase
{
    Q_OBJECT
public:
    explicit DBDatamodelLoader(DatabaseManager *databaseManager, QObject *parent = nullptr);

    static QString LOADER_TYPE_NAME;

    /*virtual*/ DatamodelBase* load(ProcessorTaskFactory *processorTaskFactory, DatamodelLoadingOptions options) override;

    /*virtual*/ void save(DatamodelBase* datamodel) override;

    /*virtual*/ QString typeName() override;

    void setDatabaseManager();

signals:

private:
    DatabaseManager *m_databaseManager = nullptr;

    QVariantMap collectValues(QSqlQuery &query, QString &classType, QString &valueGroup, QString &id, QString tableName = "");

    void loadKnownAreas(DynamicDatamodel *datamodel);
    void loadKnownRooms(DynamicDatamodel *datamodel);
    void loadValueGroups(DynamicDatamodel *datamodel);
    void loadValues(DynamicDatamodel *datamodel, QStringList valueGroupFilter);
    void loadActors(DynamicDatamodel *datamodel, QStringList classTypeFilter, QStringList valueGroupFilter);
    void loadProcessorVariables(DynamicDatamodel *datamodel);
    void loadProcessorTasks(DynamicDatamodel *datamodel);
    void loadKnownDevices(DynamicDatamodel *datamodel);
    void loadUsers(DynamicDatamodel *datamodel);

};

#endif // DBDATAMODELLOADER_H
