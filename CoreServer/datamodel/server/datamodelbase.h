#ifndef DATAMODELBASE_H
#define DATAMODELBASE_H

#include <QObject>

#include <QMap>
#include <QList>
#include "device/knowndevice.h"
#include "actor/actorbase.h"
#include "value/valuegroup.h"
#include "value/valuebase.h"
#include "processor/server/processortask.h"

#include "identifyable.h"

class DatamodelBase : public Identifyable
{
    Q_OBJECT
public:
    explicit DatamodelBase(QString id, QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    QMap<QString, KnownDevice *> knownDevices();
    QMap<QString, ValueBase*> values();
    QMap<QString, ActorBase*> actors();
    QMap<QString, ProcessorTask*> processorTasks();

protected:
    QMap<QString, KnownDevice*> m_knownDevices;
    QMap<QString, ValueGroup*> m_valueGroups;
    QMap<QString, ValueBase*> m_values;
    QMap<QString, ActorBase*> m_actors;

    QMap<QString, ProcessorTask*> m_processorTasks;

signals:

public slots:
};

#endif // DATAMODELBASE_H
