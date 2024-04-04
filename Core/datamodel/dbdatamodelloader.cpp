#include "dbdatamodelloader.h"
#include "qsqlerror.h"
#include "qsqlrecord.h"
#include "processor/processorvariable.h"
#include "user/oshuser.h"

#include <QSqlQuery>
#include <QSqlField>

QString DBDatamodelLoader::LOADER_TYPE_NAME = QStringLiteral("db");

DBDatamodelLoader::DBDatamodelLoader(DatabaseManager *databaseManager, QObject *parent)
    : DatamodelLoaderBase{parent}, m_databaseManager(databaseManager)
{

}

DatamodelBase *DBDatamodelLoader::load(ProcessorTaskFactory *processorTaskFactory, DatamodelLoadingOptions options) {
    iDebug() << Q_FUNC_INFO;

    if (m_databaseManager != nullptr) {
        DynamicDatamodel* datamodel = new DynamicDatamodel();

        loadValueGroups(datamodel);

        if (options.loadKnownAreas) {
            loadKnownAreas(datamodel);
        }

        if (options.loadActors) {
            loadActors(datamodel, options.actorClassTypeFilter);
        }

        if (options.loadValues) {
            loadValues(datamodel);
        }

        if (options.loadKnownRooms) {
            loadKnownRooms(datamodel);
        }

        if (options.loadProcessorTasks) {
            datamodel->setProcessorTaskFactory(processorTaskFactory);
            loadProcessorVariables(datamodel);
            loadProcessorTasks(datamodel);
        }

        if (options.loadUsers) {
            loadUsers(datamodel);
        }

        return datamodel;
    } else {
        iWarning() << "No database manager";
    }

    return nullptr;
}

QString DBDatamodelLoader::typeName() {
    return LOADER_TYPE_NAME;
}

void DBDatamodelLoader::save(DatamodelBase* datamodel) {
    Q_UNUSED(datamodel)
    Q_EMIT(saved());
}

void DBDatamodelLoader::loadKnownAreas(DynamicDatamodel *datamodel) {
    iInfo() << Q_FUNC_INFO;

    QSqlQuery query(*m_databaseManager->db());
    if (query.exec("SELECT * FROM dm_known_areas")) {
        while (query.next()) {
            datamodel->addKnownArea(query.value(SerializableIdentifyable::PROPERTY_ID).toString(), query.value(KnownArea::PROPERTY_NAME).toString());
        }
    } else {
        iWarning() << query.lastError();
    }

}

void DBDatamodelLoader::loadKnownRooms(DynamicDatamodel *datamodel) {
    iInfo() << Q_FUNC_INFO;

    QSqlQuery query(*m_databaseManager->db());
    if (query.exec("SELECT * FROM dm_known_rooms")) {
        while (query.next()) {
            KnownArea *knownArea = datamodel->knownArea(query.value(KnownRoom::PROPERTY_KNOWN_AREA).toString());
            datamodel->addKnownRoom(knownArea, query.value(SerializableIdentifyable::PROPERTY_ID).toString(), query.value(KnownArea::PROPERTY_NAME).toString());
        }
    } else {
        iWarning() << query.lastError();
    }
}

void DBDatamodelLoader::loadValueGroups(DynamicDatamodel *datamodel) {
    iInfo() << Q_FUNC_INFO;

    QSqlQuery query(*m_databaseManager->db());
    if (query.exec("SELECT * FROM dm_value_groups")) {
        while (query.next()) {
            datamodel->addValueGroup(query.value(SerializableIdentifyable::PROPERTY_ID).toString());
        }
    } else {
        iWarning() << query.lastError();
    }
}

void DBDatamodelLoader::loadValues(DynamicDatamodel *datamodel) {
    iInfo() << Q_FUNC_INFO;

    QSqlQuery query(*m_databaseManager->db());

    if (query.exec("SELECT * FROM dm_values")) {
        while (query.next()) {
            QString classType;
            QString valueGroup;
            QString id;
            QVariantMap values = collectValues(query, classType, valueGroup, id);
            ValueGroup* vg = datamodel->valueGroup(valueGroup);
            datamodel->addValue(classType, vg, id, values);
        }
    } else {
        iWarning() << query.lastError();
    }
}

void DBDatamodelLoader::loadActors(DynamicDatamodel *datamodel, QStringList classTypeFilter) {
    iInfo() << Q_FUNC_INFO << classTypeFilter;

    QSqlQuery query(*m_databaseManager->db());

    QString whereClause;
    if (!classTypeFilter.isEmpty()) {
        whereClause = " WHERE ";

        for (QString classType : classTypeFilter) {
            whereClause.append("ac.\"" + ValueBase::PROPERTY_CLASSTYPE + "\"='" + classType + "' OR ");
        }
        whereClause.chop(4);
    }

    if (query.exec("SELECT * FROM dm_actors ac FULL OUTER JOIN dm_actors_audio aca ON ac." + ValueBase::PROPERTY_ID + " = aca.id and ac.\"" + ValueBase::PROPERTY_VALUE_GROUP_ID + "\" = aca.\"" + ValueBase::PROPERTY_VALUE_GROUP_ID + "\" FULL OUTER JOIN dm_actors_shutter acs ON ac." + ValueBase::PROPERTY_ID + " = acs." + ValueBase::PROPERTY_ID + " and ac.\"" + ValueBase::PROPERTY_VALUE_GROUP_ID + "\" = acs.\"" + ValueBase::PROPERTY_VALUE_GROUP_ID + "\"" + whereClause)) {
        while (query.next()) {
            QString classType;
            QString valueGroup;
            QString id;
            QVariantMap values = collectValues(query, classType, valueGroup, id, "dm_actors");
            ValueGroup* vg = datamodel->valueGroup(valueGroup);
            datamodel->addActor(classType, vg, id, values);
        }
    } else {
        iWarning() << query.lastError();
    }
}

void DBDatamodelLoader::loadKnownDevices(DynamicDatamodel *datamodel) {
    iInfo() << Q_FUNC_INFO;

    QSqlQuery query(*m_databaseManager->db());

    if (query.exec("SELECT * FROM dm_known_devices")) {
        while (query.next()) {
            datamodel->addKnownDevice(query.value(SerializableIdentifyable::PROPERTY_ID).toString(), query.value(KnownDevice::PROPERTY_SERVICE_ID).toString(), query.value(KnownDevice::PROPERTY_NAME).toString());
        }
    } else {
        iWarning() << query.lastError();
    }
}

void DBDatamodelLoader::loadProcessorVariables(DynamicDatamodel *datamodel) {
    iInfo() << Q_FUNC_INFO;

    QSqlQuery query(*m_databaseManager->db());

    if (query.exec("SELECT * FROM dm_processor_variables")) {
        while (query.next()) {
            QString id = query.value(SerializableIdentifyable::PROPERTY_ID).toString();
            QString value = query.value(ProcessorVariable::PROPERTY_VALUE).toString();

            datamodel->addProcessorVariable(id, value);
        }
    } else {
        iWarning() << query.lastError();
    }
}

void DBDatamodelLoader::loadProcessorTasks(DynamicDatamodel *datamodel) {
    iInfo() << Q_FUNC_INFO;

    QSqlQuery query(*m_databaseManager->db());

    if (query.exec("SELECT * FROM dm_processor_tasks")) {
        while (query.next()) {
            QString groupId = query.value(ProcessorTaskBase::PROPERTY_GROUP_ID).toString();
            QString id = query.value(SerializableIdentifyable::PROPERTY_ID).toString();
            ProcessorTaskBase::ProcessorTaskType taskType = static_cast<ProcessorTaskBase::ProcessorTaskType>(query.value(ProcessorTaskBase::PROPERTY_TASK_TYPE).toInt());
            ProcessorTaskBase::ProcessorTaskTriggerType taskTriggerType = static_cast<ProcessorTaskBase::ProcessorTaskTriggerType>(query.value(ProcessorTaskBase::PROPERTY_TASK_TRIGGER_TYPE).toInt());
            int functionCode = query.value(ProcessorTaskBase::PROPERTY_FUNCTION_CODE).toInt();

            QStringList params;
            for (quint8 i=0;i<10;i++) {
                params << query.value(ProcessorTaskBase::PROPERTY_PARAM_PREFIX + QString::number(i)).toString();
            }

//            QString runCondition = query.value(ProcessorTaskBase::PROPERTY_RUN_CONDITION).toString();
            qint64 scheduleInterval = query.value(ProcessorTaskBase::PROPERTY_SCHEDULE_INTERVAL).toLongLong();
//            bool publishResult = query.value(ProcessorTaskBase::PROPERTY_PUBLISH_RESULT).toBool();
            bool isEnabled = query.value(ProcessorTaskBase::PROPERTY_ENABLED).toBool();

            datamodel->addProcessorTask(groupId, id, taskType, taskTriggerType, functionCode, params, scheduleInterval, isEnabled);
        }
    } else {
        iWarning() << query.lastError();
    }
}

void DBDatamodelLoader::loadUsers(DynamicDatamodel *datamodel) {
    iInfo() << Q_FUNC_INFO;

    QSqlQuery query(*m_databaseManager->db());

    if (query.exec("SELECT * FROM dm_users")) {
        while (query.next()) {
            QString id = query.value(SerializableIdentifyable::PROPERTY_ID).toString();
            QString name = query.value(OshUser::PROPERTY_NAME).toString();
            QString rights = query.value(OshUser::PROPERTY_RIGHTS).toString();
            QStringList allRights = rights.split(" ", QString::SkipEmptyParts);
            datamodel->addUser(id, name, allRights);
        }
    } else {
        iWarning() << query.lastError();
    }

}


QVariantMap DBDatamodelLoader::collectValues(QSqlQuery &query, QString &classType, QString &valueGroup, QString &id, QString tableName) {
    iInfo() << Q_FUNC_INFO;

    QVariantMap returnMap;
    QSqlRecord record = query.record();

    for (int i = 0;i<record.count();i++) {
        if ( record.field(i).name() == SerializableIdentifyable::PROPERTY_CLASSTYPE) {
            classType = query.value(i).toString();
        } else if (record.field(i).name() == SerializableIdentifyable::PROPERTY_VALUE_GROUP_ID) {
            if (tableName.isEmpty() || (!tableName.isEmpty() && record.field(i).tableName() == tableName)) {
                valueGroup = query.value(i).toString();
            } else {
                // ignore
            }
        } else if (record.field(i).name() == SerializableIdentifyable::PROPERTY_ID) {
            if (tableName.isEmpty() || (!tableName.isEmpty() && record.field(i).tableName() == tableName)) {
                id = query.value(i).toString();
            } else {
                // ignore
            }
        } else {
            returnMap.insert(record.field(i).name(), query.value(i));
        }
    }

    Q_ASSERT(!classType.isEmpty());
    Q_ASSERT(!valueGroup.isEmpty());
    Q_ASSERT(!id.isEmpty());

    return returnMap;
};

